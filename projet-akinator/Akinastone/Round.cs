using System.Collections.Generic;

namespace Akinator
{
    class Round
    {
        // Variable pour retour arriere d'un round
        private List<Attribute> attributList = new List<Attribute>();
        private Dictionary<string, int> characterScoreTab = new Dictionary<string, int>();
        private string lastBestAttrib = null;

        // Variables pour retour arriere d'un round + stockage en base
        private string question = null;
        private int number = 0;

        // Variable pour stockage en base
        private int reponse = 0;

        // Varibles pour le rapport de partie
        private Dictionary<int, string> tabReponseInWord = new Dictionary<int, string>();
        private string reponseGivenInWord = "";

        public Round(int number, Dictionary<string, int> characterScoreTab, List<Attribute> attributList)
        {
            tabReponseInWord.Add(0, "");
            tabReponseInWord.Add(1, "Oui");
            tabReponseInWord.Add(2, "Probablement");
            tabReponseInWord.Add(3, "Peut-être");
            tabReponseInWord.Add(4, "Probablement pas");
            tabReponseInWord.Add(5, "Non");

            this.number = number;
            this.characterScoreTab = characterScoreTab;
            this.attributList = attributList;
        }

        public int NumeroRound
        {
            get
            {
                return number;
            }
        }

        public int Reponse
        {
            get
            {
                return reponse;
            }

            set
            {
                reponse = value;
                if (reponse > -1)
                    reponseGivenInWord = tabReponseInWord[reponse];
            }
        }

        public Dictionary<string, int> CharacterScoreTab
        {
            get
            {
                return characterScoreTab;
            }

            set
            {
                characterScoreTab = value;
            }
        }

        internal List<Attribute> AttributList
        {
            get
            {
                return attributList;
            }

            set
            {
                attributList = value;
            }
        }

        public string LastBestAttrib
        {
            get
            {
                return lastBestAttrib;
            }

            set
            {
                lastBestAttrib = value;
            }
        }

        public string Question
        {
            get
            {
                return question;
            }

            set
            {
                question = value;
            }
        }

        public string ReponseGivenInWord
        {
            get
            {
                return reponseGivenInWord;
            }
        }
    }
}
