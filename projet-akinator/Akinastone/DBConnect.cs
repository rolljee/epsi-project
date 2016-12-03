using System;
using System.Collections.Generic;
using System.Data.SQLite;

namespace Akinator
{
    class DBConnect
    {
        SQLiteConnection m_dbConnection;

        public DBConnect()
        {
        }

        public void connectDataBase()
        {
            m_dbConnection = new SQLiteConnection("Data Source=AkinatorDB.sqlite;Version=3;");
            m_dbConnection.Open();
        }

        public void addPartie(string personnage, bool aTrouve, int nbrQuestions)
        {
            string date = DateTime.Now.ToString("dd/MM/yyyy HH:mm");
            string sqlInsert = "INSERT INTO Partie (Date, PersonnageChoisi, PersonnageTrouve, NombreQuestion)  VALUES ('" + date + "', '" + personnage + "',  " + Convert.ToInt32(aTrouve) + ", " + nbrQuestions + ")";

            SQLiteCommand command = new SQLiteCommand(sqlInsert, m_dbConnection);
            command.ExecuteNonQuery();
        }


        public void addRound(int numeroRound, string questionRound, int reponseRound, int idPartie)
        {
            string sqlInsert = "INSERT INTO Round (Numero, Question, Reponse, IdPartie) VALUES (" + numeroRound + ", '" + questionRound + "', " + reponseRound + ", " + idPartie + ")";
            SQLiteCommand command = new SQLiteCommand(sqlInsert, m_dbConnection);
            command.ExecuteNonQuery();
        }

        public int getIdOfLastInsert()
        {
            string sqlSelect = "SELECT last_insert_rowid() as LastInsertId";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);
            SQLiteDataReader reader = command.ExecuteReader();
            string result = "";

            if (reader.Read())
                result = reader["LastInsertId"].ToString();

            reader.Close();
            
            return Convert.ToInt32(result);
        }

        public string insertQuestion(string question)
        {
            bool attribNameOk = false;
            string attributInconnu = "Attr";
            SQLiteDataReader reader = null;

            for (int i = 0; attribNameOk == false ; i++)
            {
                reader = selectQuestion("Attribut", attributInconnu + i);
                
                if (!reader.HasRows)
                {
                    attributInconnu += i;
                    attribNameOk = true;
                }
            }
            reader.Close();

            string sqlInsert = "INSERT INTO Question VALUES ('" + attributInconnu + "', '" + question +"', 0)";

            Console.WriteLine("insertQuestion : " + sqlInsert);

            SQLiteCommand command = new SQLiteCommand(sqlInsert, m_dbConnection);
            command.ExecuteNonQuery();

            insertNewAttribInPersonnageTable(attributInconnu);

            return attributInconnu;
        }

        public SQLiteDataReader selectQuestion(string attribut, string rechercher)
        {
            string sqlSelect = "Select * From Question where " + attribut + " = '" + rechercher + "'";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();

            return reader;
        }

        public List<string> allName()
        {
            string sqlSelect = "Select Prenom From Personnage";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();
            List<string> listName = new List<string>();

            for (int i = 0; reader.Read(); i++)
                listName.Add(reader["Prenom"].ToString());

            return listName;
        }

        public void insertNewAttribInPersonnageTable(string newAttrib)
        {
            // Création de la colonne pour le nouvel attribut dans la table Personnage
            string sqlAlter = "ALTER TABLE Personnage ADD " + newAttrib + " INT NOT NULL DEFAULT 0";
            Console.WriteLine("insertNewAttribInPersonnageTable : " + sqlAlter);
            SQLiteCommand command = new SQLiteCommand(sqlAlter, m_dbConnection);
            
            command.ExecuteNonQuery();

            // Initialise tout les joueurs avec la reponse 0 pour ce nouvel attribut
            string sqlInsert = "Update Personnage set " + newAttrib + " = '3'";
            command = new SQLiteCommand(sqlInsert, m_dbConnection);
            Console.WriteLine("insertNewAttribInPersonnageTable : " + sqlInsert);
            command.ExecuteNonQuery();
        }

        public void insertNewPersonnage(string nomPerso)
        {
            string sqlInsert = "INSERT INTO Personnage (Prenom) VALUES ('" + nomPerso + "')" ;
            SQLiteCommand command = new SQLiteCommand(sqlInsert, m_dbConnection);

            Console.WriteLine("insertNewPersonnage : " + sqlInsert);

            command.ExecuteNonQuery();
        }

        public void updatePersonnage(Dictionary<string, string> valuesMap, string nomPerso)
        {
            string sqlUpdate = "UPDATE Personnage Set ";

            Dictionary<string, string>.KeyCollection collectionKey = valuesMap.Keys;
            Dictionary<int, string> collectionKeyConvert = new Dictionary<int, string>();
            int j = 0;

            foreach (string s in collectionKey)
            {
                collectionKeyConvert.Add(j, s);
                j++;
            }

            Dictionary<string, string>.ValueCollection collectionValue = valuesMap.Values;
            Dictionary<int, string> collectionValueConvert = new Dictionary<int, string>();
            j = 0;

            foreach (string s in collectionValue)
            {
                collectionValueConvert.Add(j, s);
                j++;
            }

            
            for (int i = 0; i < valuesMap.Count; i++)
            {
                sqlUpdate += collectionKeyConvert[i].ToString() + " = " + collectionValueConvert[i].ToString();
                if (i + 1 < valuesMap.Count)
                    sqlUpdate += ", ";
            }

            sqlUpdate += " where Prenom = '" + nomPerso + "'";

            Console.WriteLine("DBConnect - updatePersonnage() : " + sqlUpdate);
            SQLiteCommand command = new SQLiteCommand(sqlUpdate, m_dbConnection);
            command.ExecuteNonQuery();
        }

        public SQLiteDataReader selectAllPersonnages()
        {
            string sqlSelect = "Select * From Personnage";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();

            return reader;
        }

        public List<Attribute> fillListAttribut()
        {
            List<Attribute> listAttribut = new List<Attribute>();

            string sqlSelect = "Select * From Personnage";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);
            SQLiteDataReader reader = command.ExecuteReader();
            
            if (reader.Read())
            { 
                for (int i = 1; i < reader.FieldCount; i++)
                {
                    Attribute attr = new Attribute(reader.GetName(i));
                    listAttribut.Add(attr);
                    reader.Read();
                }
            }

            reader.Close();
            reader = null;
            return listAttribut;
        }

        public int countNbrQuestion()
        {
            int nbrQuestion = 0;
            string sqlSelect = "Select count(*) as nbrQuestion From Question";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);
            SQLiteDataReader reader = command.ExecuteReader();

            if (reader.Read())
                nbrQuestion = Int32.Parse(reader["nbrQuestion"].ToString());

            reader.Close();
            reader = null;
            return nbrQuestion;
        }

        // TODO Améliorer perfs
        public SQLiteDataReader selectNameAndAnswerWanted(string attribut, List<string> listPersoElimine)
        {
            string sqlSelect = "Select Prenom, " + attribut + " From Personnage";

            if (listPersoElimine.Count > 0)
            {
                sqlSelect += " where ";
                for (int i = 0; i < listPersoElimine.Count; i++)
                {
                    sqlSelect += "Prenom <> '" + listPersoElimine[i] + "'";
                    if (i+1 < listPersoElimine.Count)
                        sqlSelect += " and ";
                }
            }            
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);
            SQLiteDataReader reader = command.ExecuteReader();

            return reader;
        }

        public SQLiteDataReader selectAnswerWantedForPersonnage(string personnage)
        {
            string sqlSelect = "Select * From Personnage where Prenom = '" + personnage + "'";

            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);
            SQLiteDataReader reader = command.ExecuteReader();

            return reader;
        }

        public SQLiteDataReader selectAllPersonnagesForOneAttrib(string attribut)
        {
            string sqlSelect = "Select Prenom, " + attribut + " From Personnage";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();

            return reader;
        }


        public string getAttributFromQuestion(string question)
        {
            string attribut = "";
            string sqlSelect = "Select Attribut From Question where Libelle = '" + question + "'";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();
            if (reader.Read())
                attribut = reader["Attribut"].ToString();

            return attribut;
        }

        public string getLastTimePlayedPersonnage(string personnagePlayed)
        {
            string lastDate = "inconnu";
            string sqlSelect = "Select MAX(Date) as lastDate From Partie where PersonnageChoisi = '" + personnagePlayed + "'";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();
            if (reader.Read())
                lastDate = reader["lastDate"].ToString();

            return lastDate;
        }

        public SQLiteDataReader selectDistinctQuestionAskedToOnePerso(string persoName)
        {
            string sqlSelect = "Select distinct(Question) from Round where IdPartie in (Select Id from Partie where PersonnageChoisi = '" + persoName + "')";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();

            return reader;
        }

        public SQLiteDataReader selectResponseOfQuestionForSpecificPerso(string persoName, string specificQuestion)
        {
            string sqlSelect = "Select Reponse from Round where IdPartie in (Select Id from Partie where PersonnageChoisi = '" + persoName + "') and Question = '" + specificQuestion + "'";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();

            return reader;
        }

        public int getNbrTimePlayedPersonnage(string personnagePlayed)
        {
            int nbrPlayed = 0;
            string sqlSelect = "Select count(*) as nbrPlayed From Partie where PersonnageChoisi = '" + personnagePlayed + "'";
            SQLiteCommand command = new SQLiteCommand(sqlSelect, m_dbConnection);

            SQLiteDataReader reader = command.ExecuteReader();

            if (reader.Read())
                nbrPlayed = Int32.Parse(reader["nbrPlayed"].ToString());

            reader.Close();
            reader = null;

            return nbrPlayed;
        }

    }

}
