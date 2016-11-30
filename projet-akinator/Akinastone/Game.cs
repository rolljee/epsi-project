using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Drawing;

namespace Akinator
{
    /* 
        Game class - Main class of the game
    */
    class Game
    {
        private mainForm _gameForm = null;
        private DBConnect _dbConnect = new DBConnect();
        private List<Round> _listOfRounds = new List<Round>();
        private Jarvis _jarvis = null;
        private Round _actualRound = null;

        private int _questionNum = 0;
        private int _idPartie = -1;
        private string _persoToAdd = null;

        public Game(mainForm gameForm)
        {
            _gameForm = gameForm;
            _dbConnect.connectDataBase();

            newGame();
        }

        private string unformatSpecialCarac(string text)
        {
            // Add here and in format func other replace if necessary
            text = text.Replace('@', '\'');
            text = text.Substring(0, 1).ToUpper() + text.Substring(1);

            return text;
        }

        private string formatSpecialCarac(string text)
        {
            // Add here and in unformat func other replace if necessary
            text = text.Replace('\"', '@');
            text = text.Replace('\'', '@');
            text = text.Substring(0, 1).ToUpper() + text.Substring(1);

            return text;
        }

        public List<string> getNameListPersonnages()
        {
            List<string> nameListPerso = new List<string>();

            SQLiteDataReader reader;
            reader = _dbConnect.selectAllPersonnages();

            while (reader.Read())
                nameListPerso.Add(reader["Prenom"].ToString());

            reader.Close();

            return nameListPerso;
        }

        private void updateQuestionNum()
        {
            _questionNum++;
            _gameForm.questionNbrLb.Text = "Question N°" + _questionNum;
        }

        public void sendAnswer(int answer)
        {
            _jarvis.Answer = answer;

            if (_actualRound != null)       
                saveRound();

            // si supérieur à 19 questions, on arrête
            if (_questionNum > 19)
                displayPanelAddPerso();
            else
            {
                createRound();

                if (_listOfRounds.Count > 0)
                    displayBackButton();

                _gameForm.questionLbl.Text = unformatSpecialCarac(_jarvis.askQuestion());
             

                if (_jarvis.PersonnageTrouve)
                    proposePersonage();
                else
                {
                    updateQuestionNum();
                    // TODO Ajouter modification BG selon % de certitude   - setAkinatorBGLevel();
                }
            }
        }

        private void saveRound()
        {
            _actualRound.Reponse = _jarvis.Answer;
            _actualRound.Question = formatSpecialCarac(_gameForm.questionLbl.Text);
            _actualRound.LastBestAttrib = _jarvis.LastBestAttrib;
            _actualRound.CharacterScoreTab = new Dictionary<string, int>(_jarvis.CharacterScoreTab);

            _listOfRounds.Add(_actualRound);
        }

        private void setAkinatorBGLevel()
        {
            int findScore = 100;

            if (findScore < 0 && _gameForm.panelQuestions.BackgroundImage != Properties.Resources.akinatorLvl6)
                _gameForm.panelQuestions.BackgroundImage = Properties.Resources.akinatorLvl6;
            else if (findScore < 20 && _gameForm.panelQuestions.BackgroundImage != Properties.Resources.akinatorLvl5)
                _gameForm.panelQuestions.BackgroundImage = Properties.Resources.akinatorLvl5;
            else if (findScore < 40 && _gameForm.panelQuestions.BackgroundImage != Properties.Resources.akinatorLvl4)
                _gameForm.panelQuestions.BackgroundImage = Properties.Resources.akinatorLvl4;
            else if (findScore < 65 && _gameForm.panelQuestions.BackgroundImage != Properties.Resources.akinatorLvl3)
                _gameForm.panelQuestions.BackgroundImage = Properties.Resources.akinatorLvl3;
            else if (findScore < 80 && _gameForm.panelQuestions.BackgroundImage != Properties.Resources.akinatorLvl2)
                _gameForm.panelQuestions.BackgroundImage = Properties.Resources.akinatorLvl2;
            else if (findScore > 79 && _gameForm.panelQuestions.BackgroundImage != Properties.Resources.akinatorLvl1)
                _gameForm.panelQuestions.BackgroundImage = Properties.Resources.akinatorLvl1;
        }

        private void createRound()
        {
            _actualRound = new Round(_questionNum + 1, new Dictionary < string, int >(_jarvis.CharacterScoreTab), _jarvis.AttributList);
        }

        private void proposePersonage()
        {
            Bitmap image;

            try
            {
                string persoImage = @"Resources\Personnages\" + _jarvis.NomPersonnageTrouve + ".png";
                image = new Bitmap(persoImage);
                
            }
            catch (Exception)
            {
                string persoImage = @"Resources\Personnages\Inconnu.png";
                image = new Bitmap(persoImage);
            }

            _gameForm.answerPictureBox.BackgroundImage = image;
            displayPanelPropose();
            hideBackButton();
            _gameForm.proposePersoLbl.Text = unformatSpecialCarac(_jarvis.NomPersonnageTrouve);
        }

        // Initialize a new game
        public void newGame()
        {
            _jarvis = new Jarvis(_dbConnect);
            _listOfRounds.Clear();
            _questionNum = 0;
            createRound();
            _questionNum++;
            _gameForm.panelDefaite.Visible = false;
            _gameForm.panelVictoire.Visible = false;
            displayPanelQuestion();
            _gameForm.questionNbrLb.Text = "Question N°" + _questionNum;
            _gameForm.gameRapportGrid.Rows.Clear();

            _gameForm.questionLbl.Text = unformatSpecialCarac(_jarvis.askQuestion()); 
        }

        // Return back of a round
        public void stepBackwards()
        {
            _actualRound = _listOfRounds[_listOfRounds.Count - 1];
            _listOfRounds.RemoveAt(_listOfRounds.Count - 1);

            // Recursivité si actual round est un round de proposition de personnage
            if (_actualRound.Reponse == -1)
                stepBackwards();

            if (_listOfRounds.Count < 1)
                hideBackButton();

            _questionNum = _actualRound.NumeroRound;
            _gameForm.questionNbrLb.Text = "Question N°" + _questionNum;
            _gameForm.questionLbl.Text = unformatSpecialCarac(_actualRound.Question);

            _jarvis.LastBestAttrib = _actualRound.LastBestAttrib;
            _jarvis.AttributList.Add(new Attribute(_actualRound.LastBestAttrib));
            _jarvis.CharacterScoreTab = new Dictionary<string, int>(_actualRound.CharacterScoreTab);
        }

        public void persoClickedFromList(string personnage)
        {
            displayPanelDefaite();
            saveGameInDB(personnage, false);
        }

        public void displayPanelAddQuestion()
        {
            _gameForm.panelQuestions.Visible = false;

            _gameForm.panelAddPersonnage.Visible = false;
            _gameForm.panelListPersonnage.Visible = false;
            _gameForm.panelAddQuestion.Visible = true;
        }

        public void answerNoToPropose()
        {
            _jarvis.PersonnageTrouve = false;
            displayPanelQuestion();
            sendAnswer(-1);
        }

        public void answerYesToPropoe()
        {
            displayPanelVictoire();
            saveGameInDB(_jarvis.NomPersonnageTrouve, true);
        }

        public void saveGameInDB(string nomPersonnage, bool aTrouve)
        {
            _dbConnect.addPartie(nomPersonnage, aTrouve, _questionNum + 1);
            _idPartie = _dbConnect.getIdOfLastInsert();

            foreach (Round round in _listOfRounds)
            {
                _dbConnect.addRound(round.NumeroRound, round.Question, round.Reponse, _idPartie);
            }

            createRapport();

            _jarvis.updatePersoAnswerWanted(_listOfRounds);
        }

        public void sendQuestionToAdd(string questionToAdd, string reponse)
        {
            string question = formatSpecialCarac(questionToAdd);
            int reponseInNumeric = 0;

            switch (reponse)
            {
                case "Oui":
                    reponseInNumeric = 1;
                    break;
                case "Probablement":
                    reponseInNumeric = 2;
                    break;
                case "Ne sais pas":
                    reponseInNumeric = 3;
                    break;
                case "Probablement pas":
                    reponseInNumeric = 4;
                    break;
                case "Non":
                    reponseInNumeric = 5;
                    break;
            }

            if (_persoToAdd != null && questionToAdd != null)
            {
                // Création de la nouvelle question ainsi que de la nouvelle colonne dans la table personnage pour le nouveau attribut
                string newAttribCreated = _dbConnect.insertQuestion(formatSpecialCarac(questionToAdd));
                string persoToAddFormated = formatSpecialCarac(_persoToAdd);

                _dbConnect.insertNewPersonnage(persoToAddFormated);

                Dictionary<string, string> values = new Dictionary<string, string>();
                values.Add(newAttribCreated, reponseInNumeric.ToString());

                foreach (Round round in _listOfRounds)
                {
                    if (round.Reponse > 0)
                        values.Add(round.LastBestAttrib, round.Reponse.ToString());
                }

                _dbConnect.updatePersonnage(values, persoToAddFormated);
                saveGameInDB(persoToAddFormated, false);
            }

            displayPanelDefaite();
        }

        private void createRapport()
        {
            Dictionary<string, string> tabReponseInWord = new Dictionary<string, string>();
            tabReponseInWord.Add("0", "");
            tabReponseInWord.Add("1", "Oui");
            tabReponseInWord.Add("2", "Probablement");
            tabReponseInWord.Add("3", "Ne sais pas");
            tabReponseInWord.Add("4", "Probablement pas");
            tabReponseInWord.Add("5", "Non");

            Dictionary<string, string> tabReponseWanted = _jarvis.getDataOfOnePerso(formatSpecialCarac(_gameForm.proposePersoLbl.Text));

            int rowIndex = 0;

            foreach (Round round in _listOfRounds)
            {
                if (round.Reponse > -1)
                {
                    _gameForm.gameRapportGrid.Rows.Add(round.Question, round.ReponseGivenInWord, tabReponseInWord[tabReponseWanted[round.LastBestAttrib]]);

                    if (_gameForm.gameRapportGrid.Rows[rowIndex].Cells[1].Value.Equals(_gameForm.gameRapportGrid.Rows[rowIndex].Cells[2].Value))
                        _gameForm.gameRapportGrid.Rows[rowIndex].Cells[1].Style.ForeColor = Color.Green;
                    else
                        _gameForm.gameRapportGrid.Rows[rowIndex].Cells[1].Style.ForeColor = Color.Red;

                    rowIndex++;
                }
            }

            _gameForm.personnageTrouveRapportLbl.Text = _gameForm.proposePersoLbl.Text;
        }

        private void displayPanelPropose()
        {
            _gameForm.panelQuestions.Visible = false;
            _gameForm.panelPropose.Visible = true;

            // Preload panelContinue
            _gameForm.continuePanelPicturePB.BackgroundImage = _gameForm.answerPictureBox.BackgroundImage;
        }

        private void displayPanelQuestion()
        {
            setAkinatorBGLevel();
            _gameForm.panelQuestions.Visible = true;
        }

        private void displayStatsPerso()
        {
            _gameForm.nbrFoisJoueLbl.Text = _dbConnect.getNbrTimePlayedPersonnage(_jarvis.NomPersonnageTrouve) + " fois,";
            _gameForm.jouerDernierementLbl.Text = _dbConnect.getLastTimePlayedPersonnage(_jarvis.NomPersonnageTrouve) + ".";
        }

        private void displayPanelDefaite()
        {
            _gameForm.panelListPersonnage.Visible = false;
            _gameForm.panelAddQuestion.Visible = false;
            _gameForm.panelDefaite.Visible = true;
        }

        private void displayPanelVictoire()
        {
            displayStatsPerso();
            _gameForm.panelPropose.Visible = false;
            _gameForm.panelVictoire.Visible = true;
        }

        public void displayPanelListPerso(string persoThinked)
        {
            _persoToAdd = formatSpecialCarac(persoThinked);

            persoThinked = persoThinked.ToLower();

            // Call dbconnect for find perso with name like persoThinked, if nobody then redirect to panelAddQuestion
            // TODO change for search in db and display result found
            List<string> listName = _dbConnect.allName();
            foreach (string potentialName in listName)
            {
                string nameOfList = unformatSpecialCarac(potentialName).ToLower();
                Levenshtein leven = new Levenshtein();
                if(leven.enoughSimilitude(persoThinked, nameOfList))
                    _gameForm.listPersonnagePropose.Items.Add(nameOfList);
            }

            if (_gameForm.listPersonnagePropose.Items.Count > 0)
            {
                _gameForm.panelAddPersonnage.Visible = false;
                _gameForm.panelListPersonnage.Visible = true;
            }
            else
            {
                displayPanelAddQuestion();
            }
            
        }

        public void displayPanelAddPerso()
        {
            _gameForm.panelContinue.Visible = false;
            _gameForm.panelAddPersonnage.Visible = true;
        }

        public void displayPanelContinue()
        {
            _gameForm.panelPropose.Visible = false;
            _gameForm.panelContinue.Visible = true;
        }

        public void displayPanelRapport()
        {
            _gameForm.panelVictoire.Visible = false;
            _gameForm.panelRapport.Visible = true;
        }

        private void displayBackButton()
        {
            _gameForm.backBtn.Visible = true;
        }

        private void hideBackButton()
        {
            _gameForm.backBtn.Visible = false;
        }
    }
}
