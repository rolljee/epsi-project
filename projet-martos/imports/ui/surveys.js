import './surveys.html';
import {
    Session
} from 'meteor/session';

Template.survey.onCreated(function helloOnCreated() {
    this.date = new ReactiveVar(moment(new Date())._d);
});
Template.newSurvey.onCreated(function createdSurvey() {
    this.counter = new ReactiveVar(0);
});
Template.survey.onRendered(function () {
    Session.set("currentPage", "Survey");
});
Template.survey.events({
    "click #mysurveys"(event, instance) {
        $("#mysurveys").addClass("button-positive");
        $("#invitation").removeClass("button-positive");
        Session.set('sortOption', "mysurveys");
    },
    "click #invitation"(event, instance) {
        $("#mysurveys").removeClass("button-positive");
        $("#invitation").addClass("button-positive");
        Session.set('sortOption', "invitation");
    },
    "click .reponse"(event, instance) {
        object = {};
        object = this;
        object.email = Session.get('currentUser');
        Meteor.call('reponseSurvey', object);
    },
    "click .delete"(event, instance) {
        var self = {
            info: this,
            email: Session.get('currentUser')
        }
        Meteor.call('deleteSurvey', self, function (error, result) {
            if (error) {
                Session.set('deleteMessage', error.reason);
            } else {
                Session.set('deleteMessage', result);
            }
        });
        IonPopup.alert({
            title: "Removing Survey",
            template: Session.get('deleteMessage')
        });
    },
    "click .sendcsv"(event, instance) {
        var self = {
            info: this,
            email: Session.get('currentUser'),
            isSurvey: true
        }
        Meteor.call('sendcsv', self, function (error, result) {
            if (error) {
                Session.set('csvMessage', error.reason);
            } else {
                Session.set('csvMessage', result);
            }
        });
        IonPopup.alert({
            title: "CSV sender",
            template: Session.get('csvMessage')
        });
    }
});
Template.survey.helpers({
    user() {
        return Session.get('currentUser');
    },
    date() {
        return Template.instance().date.get();
    },
    item() {
        var surveys = [];
        var object = {
            sortOption: Session.get('sortOption'),
            email: Session.get('currentUser')
        }
        Meteor.call('findSurveyByCreationOrInvitation', object, function (error, result) {
            if (error) {
                console.log("error -->", error);
            } else {
                Session.set("sondageForCurrentUser", result);
            }
        });
        surveys = eval(Session.get("sondageForCurrentUser"));
        return surveys;
    },
    isConnectedUser() {
        return Session.get('isConnectedUser');
    }
});

Template.newSurvey.onRendered(function () {
    Session.set("currentPage", "New survey");
});
Template.newSurvey.events({
    'click #submitForm'(event, instance) {
        var contacts = [];
        var answers = [];
        var addContactToSurvey = $('.addContactToSurvey');
        $.each(addContactToSurvey, function (index, contact) {
            var isChecked = $('#check-' + index).is(':checked');
            if (isChecked) {
                contacts.push($(contact).text());
            }
        });
        answerDOM = $('.answer');
        $.each(answerDOM, function (index, answer) {
            answers.push($(answer).val());
        });
        object = {
            title: $('#title').val(),
            libelle: $('#libelle').val(),
            description: $('#description').val(),
            lieu: $('#lieu').val(),
            EndDate: $('#enddate').val(),
            answer: answers,
            contacts: contacts,
            email: Session.get('currentUser')
        }
        Meteor.call('submitSurvey', object, function (error, result) {
            if (error) {
                Session.set('submitSurveyMessage', error.reason);
            } else {
                Session.set('submitSurveyMessage', result);
            }
        });
        IonPopup.alert({
            title: "New meeting sent",
            template: Session.get('submitSurveyMessage')
        });
    },
    'click .addAnswer'(event, instance) {
        var currentpos = Template.instance().counter.get();
        $('.targetList').append(' <div id="date-' + currentpos + '"><label class="item item-input item-stacked-label"><i class="icon ion-minus-circled deleteAnswer" id="' + currentpos + '"></i><input type="text" placeholder="Other answer" class="answer"></label></div>');
        instance.counter.set(instance.counter.get() + 1);
    },
    'click .deleteAnswer'(event, instance) {
        var pos = event.currentTarget.attributes.id; // l'id de l'icon delete correspond à la pos à enlever
        $('.targetList').find("#date-" + pos.value).remove();
    },
    'click .showContact'(event, instance) {
        $(".contactDiv").toggle('slow');
    },
    'click #addContact'(event, instance) {
        var object = {
            emailOwner: Session.get('currentUser'),
            emailcontact: $("#valueContact").val(),
        };
        Meteor.call("addToContactList", object);
    }
});

Template.newSurvey.helpers({
    isConnectedUser() {
        return Session.get('isConnectedUser');
    }
});
Template.contactListForSurvey.helpers({
    contact() {
        return Contact.findOne({ owner: Session.get('currentUser') }).contact;
    }
});

Template.contactListForSurvey.helpers({
    contact() {
        var contacts = Contact.findOne({ owner: Session.get('currentUser') }).contact;
        var contactTab = [];
        var contactObject = {};

        _.each(contacts, function (contact, index) {
            contactObject = {};
            contactObject.name = contact;
            contactObject.index = index;
            contactTab.push(contactObject);
        });
        return contactTab;
    }
});
