import { Session } from 'meteor/session';
import { Router } from 'meteor/iron:router';
Template.HometemplateNotConnected.events({
    'click #connexion'(event, instance) {
        var email = instance.find('#username').value;
        var password = instance.find("#password").value;
        var object = {
            email: email,
            password: password
        };
        Meteor.call('logMeIn', object, function (error, result) {
            if (error) {
                console.log("Error while logIn", error);
                Session.set('isErrorConnexion', true);
                Session.set('connexionMessage', error.reason);
            } else {
                console.log(result);
                if (!_.isEmpty(result)) {
                    Session.set('isConnectedUser', true);
                    Session.set("idUtilisateur", result.idUtilisateur);
                    Session.set('currentUser', object.email);
                    Session.get('connexionMessage', result);
                    Session.set('isErrorConnexion', false);
                } else {
                    console.log("Connexion refusée");
                    Session.set('isErrorConnexion', true);
                }
                console.log(result);
            }
            if (Session.equals('isErrorConnexion', true)) {
                IonPopup.alert({
                    title: "Connexion...",
                    template: Session.get('connexionMessage')
                });
            }
        });
    },
    'click #register'(event, instance) {
        Router.go('/register')
    }
});
