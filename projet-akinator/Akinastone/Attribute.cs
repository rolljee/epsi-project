namespace Akinator
{
    /*
        Attribute class - Obect attribute represent each attribute and indirectly each question with their calculated data to be used by Jarvis
    */
    class Attribute
    {

        // Attribute class for stock data
        public string nom;
        public double entropieReponse1 = 0;
        public double entropieReponse2 = 0;
        public double entropieReponse3 = 0;
        public double entropieReponse4 = 0;
        public double entropieReponse5 = 0;

        public double nombreReponse1 = 0;
        public double nombreReponse2 = 0;
        public double nombreReponse3 = 0;
        public double nombreReponse4 = 0;
        public double nombreReponse5 = 0;

        public double gain = 0;

        public Attribute(string nom)
        {
            this.nom = nom;
        }
    }
}
