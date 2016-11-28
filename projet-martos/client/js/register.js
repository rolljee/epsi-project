import { Session } from 'meteor/session';
import { Router } from 'meteor/iron:router';
Template.register.events({
    'click #account-creation'(event, instance) {
        var object = {
            email: $("#username").val(),
            password: $("#password").val(),
            firstname: $("#prenom").val(),
            lastname: $("#nom").val()
        };
        Meteor.call('createAccount', object, function (err, result) {
            if (err) {
                Session.set('connexionMessage', err.reason);
            } else {
                Session.set('connexionMessage', result);
            }
        });
        IonPopup.alert({
            title: "Account creation",
            template: Session.get('connexionMessage')
        });
    },
    'click #login-page'(event, instance) {
        Router.go('/home');
    }
});