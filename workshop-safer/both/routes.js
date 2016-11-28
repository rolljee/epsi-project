
Router.route('/fiche/:_id', {
    name: "fiche",
    waitOn: function () {
        return Meteor.subscribe("Fiches");
    },
    data: function () { //Data à renvoyer dans la page
        var id = this.params._id; //Paramètre passé en url (via le :_id)
        if (id) Session.set('activeFiche', id)
    },
    onBeforeAction: function () {
        this.next();
    }
})
Router.route('/', {
    name: 'main'
});