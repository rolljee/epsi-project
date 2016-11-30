using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Akinator
{
    public partial class mainForm : Form
    {
        private Game _game;

        public mainForm()
        {
            InitializeComponent();
            _game = new Game(this);
        }

        // Ouverture du panel de présentation des personnages
        private void openPersoListForm()
        {
            ListingForm listingForm = new ListingForm();
            ImageList persoImageList = new ImageList();
            List<string> nameListPersonnage = _game.getNameListPersonnages();

            for (int i = 0; i < nameListPersonnage.Count; i++)
            {
                if (nameListPersonnage[i] != "" && nameListPersonnage[i] != null)
                { 
                    try
                    {
                        //string persoImg = @"..\..\Resources\Personnages\" + nameListPersonnage[i] + ".png";
                        string persoImg = @"Resources\Personnages\" + nameListPersonnage[i] + ".png";
                        System.Drawing.Bitmap image = new System.Drawing.Bitmap(persoImg);
                        persoImageList.ImageSize = new System.Drawing.Size(180, 250);
                        persoImageList.Images.Add(image);
                    } catch (Exception e)
                    { 
                        Console.WriteLine("[GetImageList.Error] (" + nameListPersonnage[i] + ") " + e.Message + "");
                    }
                }
            }

            listingForm.cardsListView.View = View.LargeIcon;
            listingForm.cardsListView.LargeImageList = persoImageList;

            for (int j = 0; j < persoImageList.Images.Count; j++)
            {
                ListViewItem item = new ListViewItem();
                item.ImageIndex = j;
                listingForm.cardsListView.Items.Add(item);
            }

            listingForm.nbrCardsListed.Text += " " + persoImageList.Images.Count;
            listingForm.BackColor = System.Drawing.ColorTranslator.FromHtml("#FAF4D2");
            listingForm.cardsListView.BackColor = System.Drawing.ColorTranslator.FromHtml("#FAF4D2");
            listingForm.Show();
        }

        // Boutton "Oui"
        private void yesBt_Click(object sender, EventArgs e)
        { 
            _game.sendAnswer(1);   
        }

        // Boutton "Non"
        private void noBt_Click(object sender, EventArgs e)
        {
            _game.sendAnswer(5);
        }

        // Bouton "Ne sais pas"
        private void dontKnowBt_Click(object sender, EventArgs e)
        {
            _game.sendAnswer(3);
        }

        // Bouton "Probablement"
        private void probablyBt_Click(object sender, EventArgs e)
        {
            _game.sendAnswer(2);
        }

        // Bouton "Probablement pas"
        private void probablyNotBt_Click(object sender, EventArgs e)
        {
            _game.sendAnswer(4);
        }

        // Bouton pour afficher la liste des cartes
        private void showCardsListBt_Click(object sender, EventArgs e)
        {
            openPersoListForm();
        }

        // Bouton de réponse oui à la proposition d'un personnage
        private void yesProposeButton_Click(object sender, EventArgs e)
        {
            _game.answerYesToPropoe();
        }

        // Bouton de réponse non à la proposition d'un personnage
        private void noProposeButton_Click(object sender, EventArgs e)
        {
            _game.displayPanelContinue();
        }

        // Bouton pour afficher le rapport de partie
        private void detailGameBt_Click(object sender, EventArgs e)
        {
            _game.displayPanelRapport();
        } 

        // Bouton corriger réponse
        private void backBtn_Click(object sender, EventArgs e)
        {
            _game.stepBackwards();
        }

        // Bouton de retour de la page rapport de partie
        private void backFromRapportBtn_Click(object sender, EventArgs e)
        {
            panelRapport.Visible = false;
            panelVictoire.Visible = true;
        }

        // Bouton personnage non présent dans la liste des propositions
        private void persoNotPresentBT_Click(object sender, EventArgs e)
        {
            if (addPersonnageTB.Text.Length < 2)
                noNameWrittedLbl.Visible = true;
            else
            {
                noNameWrittedLbl.Visible = false;
                Console.WriteLine("Display panel addquestion");
                _game.displayPanelAddQuestion();
            }
        }

        // Clique sur un des nom de personnages proposés
        private void listPersonnagePropose_Click(object sender, EventArgs e)
        {
            _game.persoClickedFromList(listPersonnagePropose.SelectedItems[0].Text);
        }

        // Bouton ajouter question
        private void addQuestionBT_Click(object sender, EventArgs e)
        {
            var checkedButton = panelAddQuestion.Controls.OfType<RadioButton>()
                                      .FirstOrDefault(r => r.Checked);

            if (checkedButton == null)
                noAnswerCheckedLbl.Visible = true;
            if (addNewQuestionTB.Text.Length < 5)
                noQuestionWrittedLbl.Visible = true;
            else if (addNewQuestionTB.Text.Length > 4 && checkedButton != null)
            {
                noQuestionWrittedLbl.Visible = false;
                noAnswerCheckedLbl.Visible = false;
                _game.sendQuestionToAdd(addNewQuestionTB.Text, checkedButton.Text);
            }
        }

        // Bouton oui pour continuer
        private void yesToContinueBT_Click(object sender, EventArgs e)
        {
            panelContinue.Visible = false;
            _game.answerNoToPropose();
        }

        // Bouton non pour continuer
        private void noToContinueBT_Click(object sender, EventArgs e)
        {
            _game.displayPanelAddPerso();
        }

        // Bouton d'ajout d'un personnage
        private void addPersoBT_Click(object sender, EventArgs e)
        {
            if(addPersonnageTB.Text.Length < 2)
                noNameWrittedLbl.Visible = true;
            else
            { 
                noQuestionWrittedLbl.Visible = false;
                Console.WriteLine("Passage avant panelListPerso");
                _game.displayPanelListPerso(addPersonnageTB.Text);
            }
        }

        // Bouton rejouer partie
        private void replayBt_Click(object sender, EventArgs e)
        {
            _game.newGame();
        }

        // Bouton pour quitter l'application
        private void quitBt_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        // Bouton rejouer partie
        private void replayFromDefaiteBT_Click(object sender, EventArgs e)
        {
            _game.newGame();
        }

        // Bouton pour quitter l'application
        private void quitFromDefaiteBT_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        // Bouton d'ouverture du panel administrateur
        private void adminBT_Click(object sender, EventArgs e)
        {
            AdminForm form = new AdminForm();
            form.Visible = true;
        }

        // Bouton jouer de la page de démarrage
        private void playBT_Click(object sender, EventArgs e)
        {
            panelAccueil.Visible = false;
            panelQuestions.Visible = true;
        }

        private void maybeRB_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
