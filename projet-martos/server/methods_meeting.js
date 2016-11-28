import { HTTP } from 'meteor/http';
import { Meteor } from 'meteor/meteor';

Meteor.methods({
  findAllRDVForCurrentUser: function (object) {
    var back = [];
    const url = "com.surveymeeting.entity.rdv/owns/";
    const final_url = URL + url + object.email;
    try {
      back = HTTP.get(final_url);
    } catch (error) {
      console.log("Exception : ", error);
    }
    return back.content;
  },
  findMeetingByState: function (object) {
    var url;
    var back = [];
    object.sortOption == "in_progress" ? url = "com.surveymeeting.entity.rdv/inprogress/" : url = "com.surveymeeting.entity.rdv/finished/";
    const final_url = URL + url + object.email;
    try {
      back = HTTP.get(final_url);
      _.each(back.data, function (meeting) {
        meeting = _.extend(meeting, { isMeeting: true });
      });
    } catch (error) {
      console.log("Exception", error);
    }
    return back.data;
  },
  findMeetingByCreationOrInvitation: function (object) {
    var url;
    var back = [];
    object.sortOption === "invitation" ? url = "com.surveymeeting.entity.rdv/owns/" : url = "com.surveymeeting.entity.rdv/finished/";
    const final_url = URL + url + object.email;
    try {
      back = HTTP.get(final_url);
    } catch (error) {
      console.log("Exception", error);
    }
    return back.data;
  },
  reponseMeeting: function (object) {
    var url = "com.surveymeeting.entity.reponserdv/";
    try {
      HTTP.call("POST", URL + url, {
        data: {
          "id_rdv": object._persistence_idRdv_vh.row['surveyMeetingBDD.proposition_rdv.id_rdv'],
          "mail_utilisateur": object.email,
          "id_proposition": object.idProposition
        },
        headers: { "content-type": "application/json" }
      });
    } catch (error) {
      console.log("Erreur lors de l'ajout : ", error);
    }
    Email.send({
      to: "n.riquelmebareiro@gmail.com",//object.email,
      from: "no-reply@surveymeeting.com",
      subject: "You answered at one Meeting",
      text: "You answered the question :" + object.libelle
    });
  },
  submitRdv: function (object) {
    console.log(JSON.stringify(object));
    var url = "com.surveymeeting.entity.rdv/insert";
    var inserter = {};
    inserter.propositionRdv = [];
    inserter.inviteRdv = [];
    inserter["libelle"] = object.libelle;
    inserter["lieu"] = object.lieu;
    inserter["description"] = object.description;
    inserter["mail_utilisateur"] = object.email;
    inserter["debut"] = ""//new Date();
    inserter["fin"] = ""//object.EndDate;

    _.each(object.answer, function (res) {
      var sousObjReponse = {};
      var splitted = res.split("-");
      sousObjReponse["heure_debut"] = splitted[0];
      sousObjReponse["heure_fin"] = splitted[1];
      inserter.propositionRdv.push(sousObjReponse);
    });
    _.each(object.contacts, function (contact) {
      var sousObjContact = {};
      sousObjContact["mail_utilisateur"] = contact;
      inserter.inviteRdv.push(sousObjContact);
    });
    try {
      //HTTP.post(URL + url, JSON.stringify(inserter));
      HTTP.call("post", URL + url, { data: inserter, headers: { "content-type": "application/json" } })
      console.log(URL + url, JSON.stringify(inserter));
    } catch (error) {
      throw new Meteor.Error("An error occured",
        "Something went wrong, we apologize for the inconvenient");
    }
  },
  deleteMeeting: function (object) {
    console.log('deleteMeeting', object);
    var errorstack = 'Meeting has been deleted';
    if (object.email === object.info.mailUtilisateur) {
      try {
        var url = "com.surveymeeting.entity.rdv/" + object.info.idRdv;
        HTTP.del(URL + url);
      } catch (error) {
        console.log(error);
        errorstack = "Something went wrong, we apologize for the inconvenient";
        throw new Meteor.Error("An error occured",
          "Something went wrong, we apologize for the inconvenient");
      }
    } else {
      throw new Meteor.Error("Not owner of the meeting",
        "You are not allowed to execute this action, you are not the owner of this meeting");
    }
    return errorstack;
  }
});
