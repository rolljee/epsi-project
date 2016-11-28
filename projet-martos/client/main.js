import {
    Template
} from 'meteor/templating';
import {
    ReactiveVar
} from 'meteor/reactive-var';

import {
    Session
} from 'meteor/session';


import './main.html';
import '../imports/api/routes.js'
import '../imports/ui/meetings.js'
import '../imports/ui/profile.js'
import '../imports/ui/surveys.js'

//Global Session variable
Session.setDefault('isConnectedUser', false);
Session.setDefault('sortOption', "in_progress");
Session.setDefault('isErrorConnexion', false);


Template.Hometemplate.onCreated(function helloOnCreated() {
    this.date = new ReactiveVar(moment(new Date())._d);
});

Template.Hometemplate.helpers({
    user() {
        return Session.get('currentUser');
    },
    date() {
        return Template.instance().date.get();
    },
    item() {
        var tab_formated_both = [];
        var object = {
            sortOption: Session.get('sortOption'),
            email: Session.get('currentUser')
        }
        Meteor.call('findSurveyByState', object, function (error, result) {
            if (error) {
                console.log("error -->", error);
            } else {
                Session.set("SurveyState", result);
            }
        });
        Meteor.call('findMeetingByState', object, function (error, result) {
            if (error) {
                console.log("error -->", error);
            } else {
                Session.set("MeetingState", result);
            }
        });
        var surveyTab = eval(Session.get('SurveyState'));

        _.each(surveyTab, function (survey) {
            _.each(survey.reponseSondageCollection, function (reponse) {
                if (reponse.reponseSondagePK.mailUtilisateur === Session.get('currentUser')) {
                    Session.set("selectedPostSurvey", reponse.reponseSondagePK.mailUtilisateur + "/" + reponse.reponseSondagePK.idProposition);
                }
            });
        });
        var rdvTab = eval(Session.get('MeetingState'));
        _.each(rdvTab, function (meeting) {
            _.each(meeting.reponseRdvCollection, function (reponse) {
                if (reponse.reponseRdvPK.mailUtilisateur === Session.get('currentUser')) {
                    Session.set("selectedPostMeeting", reponse.reponseRdvPK.mailUtilisateur + "/" + reponse.reponseRdvPK.idProposition);
                }
            });
        });
        tab_formated_both = _.shuffle(_.union(surveyTab, rdvTab));
        console.log(tab_formated_both);
        return tab_formated_both;
    },
    setCheckedSurvey() {
        var toCheck = false;
        if (Session.equals("selectedPostSurvey", Session.get('currentUser') + "/" + this.idProposition)) {
            toCheck = true;
        }
        return toCheck ? "checked" : "";
    },
    setCheckedMeeting() {
        var toCheck = false;
        if (Session.equals("selectedPostMeeting", Session.get('currentUser') + "/" + this.idProposition)) {
            toCheck = true;
        }
        return toCheck ? "checked" : "";
    }
});

Template.Hometemplate.events({
    "click #in_progress"(event, instance) {
        $("#in_progress").addClass("button-positive");
        $("#finished").removeClass("button-positive");
        Session.set('sortOption', "in_progress");
    },
    "click #finished"(event, instance) {
        $("#in_progress").removeClass("button-positive");
        $("#finished").addClass("button-positive");
        Session.set('sortOption', "finished");
    },
    "click .sondageicon"(event, instance) {
        $("#inviteSondage-" + this.idSondage).toggle("slow");
    },
    "click .meetingicon"(event, instance) {
        $("#inviteMeeting-" + this.idRdv).toggle("slow");
    }
});

Template.home.helpers({
    isConnectedUser() {
        return Session.get('isConnectedUser');
    }
});
