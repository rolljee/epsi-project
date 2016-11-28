import './profile.html';
import { Session } from 'meteor/session';

Template.system.onCreated(function helloOnCreated() {
  // counter starts at 0
  this.date = new ReactiveVar(moment(new Date()));
});
Template.system.onRendered(function () {
  Session.set("currentPage", "Settings");
});
Template.system.helpers({
  user() {
    return Session.get('currentUser');
  },
  lastTime() {
    return Template.instance().date.get();
  },
  isConnectedUser() {
    return Session.get('isConnectedUser');
  }
});

Template.system.events({
  'click .contactList'(event, instance) {
    $('.listeContact').toggle("slow");
  },
  'click .passwordDiv'(event, instance) {
    $('.password').toggle("slow");
  },
  'click .user-email'(event, instance) {
    $('.email').toggle("slow");
  },
  'click .aboutusDiv'(event, instance) {
    $('.aboutus').toggle("slow");
  },
  'click .notificationDiv'(event, instance) {
    $('.notifications').toggle("slow");
  },
  'click .disconnect'(event, instance) {
    Session.set('isConnectedUser', false);
  }
});
Template.changeEmail.events({
  'click #changeEmail'(event, instance) {
    object = {
      oldEmail: $("#oldEmail").val(),
      newEmail: $("#newEmail").val(),
    }
    Meteor.call('changeEmail', object, function (err, result) {
      if (err) {
        console.log(err)
        Session.set('resultEmail', err.reason);
      } else {
        Session.set('resultEmail', "Email changed succesfully.");
      }
      IonPopup.alert({
        title: "Modifying Email",
        template: Session.get('resultEmail')
      });
    });
  }
});
Template.changePassword.events({
  'click #changepassword'(event, instance) {
    object = {
      newpassword: $("#newpassword").val(),
      oldpassword: $("#oldpassword").val(),
      confirmnewpassword: $("#confirmnewpassword").val(),
      _id: Session.get("idUtilisateur")
    }
    Meteor.call('changepassword', object, function (err, result) {
      if (err) {
        console.log(err)
        Session.set('resultPassword', err.reason);
      } else {
        Session.set('resultPassword', result);
      }
      IonPopup.alert({
        title: "Modifying password",
        template: Session.get('resultPassword')
      });
    });
  }
});
Template.notifications.helpers({
  isChecked() {
    return 'checked'; // Return Vide ou checked en fonction de la réponse
  }
});
Template.contactList.helpers({
  contact() {
    return Contact.findOne({ owner: Session.get('currentUser') }).contact;
  }
});

Template.contactList.events({
  'click #addContact'(event, instance) {
    var object = {
      emailOwner: Session.get('currentUser'),
      emailcontact: $("#contactToAdd").val(),
    };
    Meteor.call("addToContactList", object, function (err, result) {
      if (err) {
        Session.set('resultAddContact', err.reason);
      } else {
        Session.set('resultAddContact', "Update accepted");
      }
      IonPopup.alert({
        title: "New contact",
        template: Session.get('resultAddContact')
      });
    });
  },
  'click .removeContact'(event, instance) {
    console.log(this);
    var object = {};
    var information = "";
    _.each(this, function (info) {
      information += info;
    });
    object.emailOwner = Session.get('currentUser');
    object.emailcontact = information;
    Meteor.call('removeContact', object);
  }
});
