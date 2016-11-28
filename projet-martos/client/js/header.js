import { Session } from 'meteor/session';

Template.header.onRendered(function () {
    Session.set("currentPage", "Home");
});

Template.header.helpers({
    currentPage() {
        return Session.get("currentPage");
    },
    displaySigle() {
        if (Session.equals("currentPage", "New meeting") || Session.equals("currentPage", "New survey")) {
            return 'ion-ios-arrow-back';
        } else if (Session.equals("currentPage", "Meeting") || Session.equals("currentPage", "Survey")) {
            return 'ion-plus';
        } else {
            return '';
        }
    }
});
Template.header.events({
    'click #settings'(event, instance) {
        Router.go('/profile');
    },
    'click #commandButton'(event, instance) {
        if (Session.equals("currentPage", "Meeting")) {
            Router.go('/createMeeting');
        }
        if (Session.equals("currentPage", "Survey")) {
            Router.go('/createSurvey');
        }
        if (Session.equals("currentPage", "New meeting")) {
            Router.go('/meetings');
        }
        if (Session.equals("currentPage", "New survey")) {
            Router.go('/surveys');
        }
    },
});
