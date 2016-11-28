import './meetings.html';
import { Session } from 'meteor/session';

Template.meeting.onCreated(function helloOnCreated() {
    this.date = new ReactiveVar(moment(new Date())._d);
});

Template.newMeeting.onCreated(function createdMeeting() {
    this.counter = new ReactiveVar(0);
});

Template.meeting.onRendered(function () {
    Session.set("currentPage", "Meeting");
});
Template.meeting.events({
    "click #mymeetings"(event, instance) {
        $("#mymeetings").addClass("button-positive");
        $("#invitation").removeClass("button-positive");
        Session.set('sortOption', "mymeetings");
    },
    "click #invitation"(event, instance) {
        $("#mymeetings").removeClass("button-positive");
        $("#invitation").addClass("button-positive");
        Session.set('sortOption', "invitation");
    },
    "click .reponse"(event, instance) {
        object = {};
        object = this;
        object.email = Session.get('currentUser');
        Meteor.call('reponseMeeting', object);

    },
    "click .delete"(event, instance) {
        var self = {
            info: this,
            email: Session.get('currentUser')
        }
        Meteor.call('deleteMeeting', self, function (error, result) {
            if (error) {
                Session.set('deleteMessage', error.reason);
            } else {
                Session.set('deleteMessage', result);
            }
        });
        IonPopup.alert({
            title: "Removing meeting",
            template: Session.get('deleteMessage')
        });
    },
    "click .sendcsv"(event, instance) {
        var self = {
            info: this,
            email: Session.get('currentUser'),
            isMeeting: true
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
Template.meeting.helpers({
    user() {
        return Session.get('currentUser');
    },
    date() {
        return Template.instance().date.get();
    },
    contactCounter() {
        return Template.instance().contactCounter.get();
    },
    item() {
        var meetings = [];
        var object = {
            sortOption: Session.get('sortOption'),
            email: Session.get('currentUser')
        }
        Meteor.call('findMeetingByCreationOrInvitation', object, function (error, result) {
            if (error) {
                console.log("error -->", error);
            } else {
                Session.set("meetingForCurrentUser", result);
            }
        });
        meetings = eval(Session.get("meetingForCurrentUser"));
        return meetings;
    },
    isConnectedUser() {
        return Session.get('isConnectedUser');
    }
});

Template.newMeeting.onRendered(function () {
    Session.set("currentPage", "New meeting");
});

Template.newMeeting.events({
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
        Meteor.call('submitRdv', object, function (error, result) {
            if (error) {
                Session.set('submitRdvMessage', error.reason);
            } else {
                Session.set('submitRdvMessage', result);
            }
        });
        IonPopup.alert({
            title: "New meeting sent",
            template: Session.get('submitRdvMessage')
        });
    },
    'click .addAnswer'(event, instance) {
        const currentpos = Template.instance().counter.get();
        $('.targetList').append(' <div id="date-' + currentpos + '"><label class="item item-input item-stacked-label"><i class="icon ion-minus-circled deleteAnswer" id="' + currentpos + '"></i><input type="text" placeholder="hh:mm (beginning) - hh:mm (end)" class="answer"></label></div>');
        instance.counter.set(instance.counter.get() + 1);
    },
    'click .deleteAnswer'(event, instance) {
        const pos = event.currentTarget.attributes.id; // l'id de l'icon delete correspond à la pos à enlever
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
    },
});
Template.newMeeting.helpers({
    isConnectedUser() {
        return Session.get('isConnectedUser');
    }
});
Template.contactListForMeeting.helpers({
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