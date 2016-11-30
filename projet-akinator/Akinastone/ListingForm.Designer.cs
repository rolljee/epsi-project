namespace Akinator
{
    partial class ListingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ListingForm));
            this.cardsListView = new System.Windows.Forms.ListView();
            this.nbrCardsListed = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cardsListView
            // 
            this.cardsListView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.cardsListView.BackColor = System.Drawing.Color.White;
            this.cardsListView.Location = new System.Drawing.Point(0, 0);
            this.cardsListView.Name = "cardsListView";
            this.cardsListView.Size = new System.Drawing.Size(1011, 575);
            this.cardsListView.TabIndex = 0;
            this.cardsListView.UseCompatibleStateImageBehavior = false;
            // 
            // nbrCardsListed
            // 
            this.nbrCardsListed.AutoSize = true;
            this.nbrCardsListed.Location = new System.Drawing.Point(12, 578);
            this.nbrCardsListed.Name = "nbrCardsListed";
            this.nbrCardsListed.Size = new System.Drawing.Size(129, 13);
            this.nbrCardsListed.TabIndex = 1;
            this.nbrCardsListed.Text = "Nombre de personnages :";
            // 
            // ListingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1010, 595);
            this.Controls.Add(this.nbrCardsListed);
            this.Controls.Add(this.cardsListView);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ListingForm";
            this.Text = "Liste des personnages de South-Park";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.ListView cardsListView;
        internal System.Windows.Forms.Label nbrCardsListed;
    }
}