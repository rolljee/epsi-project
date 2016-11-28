import { Session } from 'meteor/session';
import { Router } from 'meteor/iron:router';
Template.forgotpassword.events({
    'click #sendpassword'(event, instance) {
        Meteor.call('forgotpassword', $('#email').val(), function (error, result) {
            if (error) {
                Session.set('errorpassword', error.reason);
            } else {
                Session.set('errorpassword', 'Email Sent !');
            }
            IonPopup.alert({
                title: "Forgot password",
                template: Session.get('errorpassword')
            });
        });
    },
    'click #goHomePage'(event, instance) {
        Router.go('/home');
    }
});