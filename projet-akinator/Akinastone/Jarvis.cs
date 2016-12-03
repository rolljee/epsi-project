using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Linq;

namespace Akinator
{
    /* 
        Jarvis class - Is the core of the game. He analyze and think better than us. He analyse, find and propose the good personnage for the game
    */
    class Jarvis
    {
        // Dictionnaire generale des values pour scoring (ne change jamais)
        int[,] scoreTabValues = {
           { 3,1,-1,-2,-3},
           { 1,3,1,-1,-2},
           {-1,1,3,1,-1},
           {-2,-1,1,3,1},
           {-3,-2,-1,1,3}};

        // Dictionnaire de score des personnages pour la question en cours
        private Dictionary<string, int> _characterScoreTab = new Dictionary<string, int>();

        // Liste des nom des personnages déja proposés
        private List<string> _listPersoElimine = new List<string>();

        // Liste des nom des personnages ayant le score le plus élevé ce round ci (Tous au début)
        private List<string> _listPersoBestScore = new List<string>();

        // Liste des attributs pour ce round ci (avec leur entropie pour chaque classe 1,2,3,4,5)
        private List<Attribute> _attributList = new List<Attribute>();

        private DBConnect _dbConnect = null;
        private int _answer = 0;
        private int _indexActualAttribute = 0;
        private int _nbrPersonnages = 0;
        private string _lastBestAttrib = null;
        private string _nomPersonnageTrouve = null;
        private bool _personnageTrouve = false;
        private int _limitQuestion = 0;


        public Jarvis(DBConnect dbConnect)
        {
            _dbConnect = dbConnect;

            setScoringTab();
            _attributList = dbConnect.fillListAttribut();
            _limitQuestion = _dbConnect.countNbrQuestion();
        }

        public void fillListPersoBestScore()
        {
            int scoreAll = 0, scoreBest = 0, scoreMax = 0;

            for (int i = 0; i <  _characterScoreTab.Count; i++)
                if (_characterScoreTab.Values.ElementAt(i) > scoreMax)
                    scoreMax = _characterScoreTab.Values.ElementAt(i);
           
            for (int i = 0; i < _characterScoreTab.Count; i++)
            {
                scoreAll += _characterScoreTab.Values.ElementAt(i);
                if (_characterScoreTab.Values.ElementAt(i) == scoreMax)
                {
                    scoreBest += _characterScoreTab.Values.ElementAt(i);
                    _listPersoBestScore.Add(_characterScoreTab.Keys.ElementAt(i));
                }
            }
        }

        private void updateScore(string attribut)
        {
            SQLiteDataReader reader = _dbConnect.selectNameAndAnswerWanted(attribut, _listPersoElimine);

            for (int i = 0; reader.Read() && i <  reader.StepCount; i++)
                _characterScoreTab[reader["Prenom"].ToString()] += scoreTabValues[Convert.ToInt32(reader[attribut].ToString()) - 1, _answer - 1];
        }

        public string askQuestion()
        {
            string questionToAsk = "";
            _listPersoBestScore.Clear();

            // TODO Optimiser le update score avec list perso elimine
            if (_answer == -1)
            {   
                _characterScoreTab.Remove(_nomPersonnageTrouve);
                _listPersoElimine.Add(_nomPersonnageTrouve);
            }

            if (_answer > 0)
                updateScore(_lastBestAttrib);

            if (_listPersoBestScore.Count == 1)
                _personnageTrouve = true;

            fillListPersoBestScore();
            _nbrPersonnages = _listPersoBestScore.Count();

            if (_nbrPersonnages > 1)
            {
                for (int i = 0; i < _attributList.Count(); i++)
                {
                    _indexActualAttribute = i;
                    calculEntropiePourAttribut();
                    calculGain();
                }

                double bestGain = -5000;
                string attributBestGain = "";

                foreach (Attribute attrib in _attributList)
                {
                    if (attrib.gain > bestGain)
                    {
                        bestGain = attrib.gain;
                        attributBestGain = attrib.nom;
                    }
                }

                _lastBestAttrib = attributBestGain;

                int attrToRemove = 0, index = 0;

                foreach (Attribute attr in _attributList)
                {
                    if (attr.nom == attributBestGain)
                        attrToRemove = index;
                    index++;
                }

                _attributList.RemoveAt(attrToRemove);

                SQLiteDataReader reader = _dbConnect.selectQuestion("Attribut", attributBestGain);
                if (reader.Read())
                    questionToAsk = reader["Libelle"].ToString();

                reader.Close();
                reader = null;
            }
            else
            {
                _personnageTrouve = true;
                NomPersonnageTrouve = _listPersoBestScore.ElementAt(0).ToString();
                questionToAsk = "Je pense que ton personnage est " + _nomPersonnageTrouve;
            }
            return questionToAsk;
        }

        public Dictionary<string, string> getDataOfOnePerso(string persoName)
        {
            Dictionary<string, string> persoData = new Dictionary<string, string>();

            SQLiteDataReader reader = _dbConnect.selectAnswerWantedForPersonnage(persoName);
            if (reader.Read())
                for (int i = 1; i < reader.FieldCount; i++)
                    persoData.Add(reader.GetName(i), reader[i].ToString());

            reader.Close();
            reader = null;
            return persoData;
        }

        // TODO : Mettre la fonction en asynchrone
        public void updatePersoAnswerWanted(List<Round> listOfRounds)
        {
            SQLiteDataReader reader1;
            SQLiteDataReader reader2;
            bool updateRequired = false;
            int nbrAnswer1 = 0, nbrAnswer2 = 0, nbrAnswer3 = 0, nbrAnswer4 = 0, nbrAnswer5 = 0, bestAnswer = 0, answerCount = 0;
            Dictionary<string, string> persoDataDictionary = getDataOfOnePerso(_nomPersonnageTrouve);
            Dictionary<string, string> newAnswersWanted = new Dictionary<string, string>();
            bool switchQuestion = false;

            reader1 = _dbConnect.selectDistinctQuestionAskedToOnePerso(_nomPersonnageTrouve);
            while (reader1.Read())
            {
                string question = reader1["Question"].ToString();
                Console.WriteLine("\n@Question : " + question);
                reader2 = _dbConnect.selectResponseOfQuestionForSpecificPerso(_nomPersonnageTrouve, question);
                int answerGiven = 0;
                while (reader2.Read())
                {
                    nbrAnswer1 = 0; nbrAnswer2 = 0; nbrAnswer3 = 0; nbrAnswer4 = 0; nbrAnswer5 = 0; answerCount = 0;
                    answerGiven = Int32.Parse(reader2["Reponse"].ToString());
                    switch (answerGiven)
                    {
                        case 1:
                            nbrAnswer1++;
                            if (nbrAnswer1 > answerCount)
                            {
                                answerCount = nbrAnswer1;
                                bestAnswer = 1;
                            }
                            break;
                        case 2:
                            nbrAnswer2++;
                            if (nbrAnswer2 > answerCount)
                            {
                                answerCount = nbrAnswer2;
                                bestAnswer = 2;
                            }
                            break;
                        case 3:
                            nbrAnswer3++;
                            if (nbrAnswer3 > answerCount)
                            {
                                answerCount = nbrAnswer3;
                                bestAnswer = 3;
                            }
                            break;
                        case 4:
                            nbrAnswer4++;
                            if (nbrAnswer4 > answerCount)
                            {
                                answerCount = nbrAnswer4;
                                bestAnswer = 4;
                            }
                            break;
                        case 5:
                            nbrAnswer5++;
                            if (nbrAnswer5 > answerCount)
                            {
                                answerCount = nbrAnswer5;
                                bestAnswer = 5;
                            }
                            break;
                        case -1:
                            switchQuestion = true;
                            break;
                        default:
                            break;
                    }

                    
                } // Fin While Reader2

                if (!switchQuestion)
                {
                    string attr = _dbConnect.getAttributFromQuestion(question);
                    if (attr != "")
                    { 
                        string attrAnswer = persoDataDictionary[attr];
                        if (attrAnswer != "")
                        { 
                            if (answerGiven != -1 && Int32.Parse(attrAnswer) != bestAnswer)
                            {
                                newAnswersWanted.Add(_dbConnect.getAttributFromQuestion(question), bestAnswer.ToString());
                                updateRequired = true;
                            }
                        }
                    }
                }

                reader2.Close();
            } // Fin While Reader1

            if (updateRequired)
            {
                Console.WriteLine(newAnswersWanted.Count);
                _dbConnect.updatePersonnage(newAnswersWanted, _nomPersonnageTrouve);
                Console.WriteLine("Personnage updated");
            }

            reader1.Close();
            reader1 = null;
            reader2 = null;
        }

        public void setScoringTab()
        {
            SQLiteDataReader reader = _dbConnect.selectAllPersonnages();

            while (reader.Read())
                _characterScoreTab.Add(reader["Prenom"].ToString(), 0);

            reader.Close();
            reader = null;
        }

        private double logDeux(double value)
        {
            return Math.Log(value, 2.0);
        }

        public void calculNbrParReponse()
        {
            string actualAttrib = _attributList.ElementAt(_indexActualAttribute).nom;
            _attributList.ElementAt(_indexActualAttribute).nombreReponse1 = 0;
            _attributList.ElementAt(_indexActualAttribute).nombreReponse2 = 0;
            _attributList.ElementAt(_indexActualAttribute).nombreReponse3 = 0;
            _attributList.ElementAt(_indexActualAttribute).nombreReponse4 = 0;
            _attributList.ElementAt(_indexActualAttribute).nombreReponse5 = 0;

            SQLiteDataReader reader = _dbConnect.selectAllPersonnagesForOneAttrib(actualAttrib);

            while (reader.Read())
            {
                if (_listPersoBestScore.Contains(reader[0].ToString()))
                {
                    switch (reader[1].ToString())
                    {
                        case "1":
                            _attributList.ElementAt(_indexActualAttribute).nombreReponse1 += 1;
                            break;
                        case "2":
                            _attributList.ElementAt(_indexActualAttribute).nombreReponse2 += 1;
                            break;
                        case "3":
                            _attributList.ElementAt(_indexActualAttribute).nombreReponse3 += 1;
                            break;
                        case "4":
                            _attributList.ElementAt(_indexActualAttribute).nombreReponse4 += 1;
                            break;
                        case "5":
                            _attributList.ElementAt(_indexActualAttribute).nombreReponse5 += 1;
                            break;
                    }
                }
            }

            reader.Close();
            reader = null;
        }

        public void calculGain()
        {

            double entropieGenerale = calculEntropieGenerale();
            Attribute actualAttrib = _attributList.ElementAt(_indexActualAttribute);

            double resultReponse1 = actualAttrib.nombreReponse1 / _nbrPersonnages * actualAttrib.entropieReponse1;
            double resultReponse2 = actualAttrib.nombreReponse2 / _nbrPersonnages * actualAttrib.entropieReponse2;
            double resultReponse3 = actualAttrib.nombreReponse3 / _nbrPersonnages * actualAttrib.entropieReponse3;
            double resultReponse4 = actualAttrib.nombreReponse4 / _nbrPersonnages * actualAttrib.entropieReponse4;
            double resultReponse5 = actualAttrib.nombreReponse5 / _nbrPersonnages * actualAttrib.entropieReponse5;

            double gain = entropieGenerale - (resultReponse1 + resultReponse2 + resultReponse3 + resultReponse4 + resultReponse5);
            _attributList.ElementAt(_indexActualAttribute).gain = gain;
        }

        public double calculEntropieGenerale()
        {
            double entropieGenerale = 0;
            double surNbrPersonne = 1.00 / (double)_nbrPersonnages;

            for (int i = 0; i < _nbrPersonnages; i++)
                entropieGenerale += surNbrPersonne * logDeux(surNbrPersonne);

            return -entropieGenerale;
        }

        public void calculEntropiePourAttribut()
        {
            calculNbrParReponse();
   
            _attributList.ElementAt(_indexActualAttribute).entropieReponse1 = calculEntropie(_attributList.ElementAt(_indexActualAttribute).nombreReponse1);
            _attributList.ElementAt(_indexActualAttribute).entropieReponse2 = calculEntropie(_attributList.ElementAt(_indexActualAttribute).nombreReponse2);
            _attributList.ElementAt(_indexActualAttribute).entropieReponse3 = calculEntropie(_attributList.ElementAt(_indexActualAttribute).nombreReponse3);
            _attributList.ElementAt(_indexActualAttribute).entropieReponse4 = calculEntropie(_attributList.ElementAt(_indexActualAttribute).nombreReponse4);
            _attributList.ElementAt(_indexActualAttribute).entropieReponse5 = calculEntropie(_attributList.ElementAt(_indexActualAttribute).nombreReponse5);          
        }

        public double calculEntropie(double nbrPourUneReponse)
        {
            double resultatEntropie = 0;

            for (int i = 0; i < nbrPourUneReponse; i++)
            {
                resultatEntropie += 1/ nbrPourUneReponse * logDeux(1/ nbrPourUneReponse);
            }

            return -resultatEntropie;
        }

        public int Answer
        {
            get
            {
                return _answer;
            }

            set
            {
                _answer = value;
            }
        }

        public bool PersonnageTrouve
        {
            get
            {
                return _personnageTrouve;
            }

            set
            {
                _personnageTrouve = value;
            }
        }

        public string NomPersonnageTrouve
        {
            get
            {
                return _nomPersonnageTrouve;
            }

            set
            {
                _nomPersonnageTrouve = value;
            }
        }

        public Dictionary<string, int> CharacterScoreTab
        {
            get
            {
                return _characterScoreTab;
            }

            set
            {
                _characterScoreTab = value;
            }
        }

        internal List<Attribute> AttributList
        {
            get
            {
                return _attributList;
            }

            set
            {
                _attributList = value;
            }
        }

        public string LastBestAttrib
        {
            get
            {
                return _lastBestAttrib;
            }

            set
            {
                _lastBestAttrib = value;
            }
        }

        public int LimitQuestion
        {
            get
            {
                return _limitQuestion;
            }

            set
            {
                _limitQuestion = value;
            }
        }
    }
}
