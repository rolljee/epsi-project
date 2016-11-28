import { HTTP } from 'meteor/http';
import { Meteor } from 'meteor/meteor';


Meteor.methods({
  findAllSurveyForCurrentUser: function (object) {
    var back = [];
    const url = "com.surveymeeting.entity.sondage/owns/";
    const final_url = URL + url + object.email;
    try {
      back = HTTP.get(final_url);
    } catch (error) {
      console.log("Exception : ", error);
    }

    return back.data;
  },
  findSurveyByState: function (object) {
    var url;
    var back = [];
    object.sortOption === "in_progress" ? url = "com.surveymeeting.entity.sondage/inprogress/" : url = "com.surveymeeting.entity.sondage/finished/";
    const final_url = URL + url + object.email;
    try {
      back = HTTP.get(final_url);
    } catch (error) {
      console.log("Exception : ", error);
    }

    return back.content;
  },
  findSurveyByCreationOrInvitation: function (object) {
    var url;
    var back = [];
    object.sortOption === "invitation" ? url = "com.surveymeeting.entity.sondage/owns/" : url = "com.surveymeeting.entity.sondage/finished/";
    const final_url = URL + url + object.email;
    try {
      back = HTTP.get(final_url);
    } catch (error) {
      console.log("Exception : ", error);
    }
    return back.content;
  },
  reponseSurvey: function (object) {
    console.log(object);
    var url = "com.surveymeeting.entity.reponsesondage/";
    console.log(object._persistence_idSondage_vh.row);
    try {
      HTTP.call("POST", URL + url, {
        data: {
          "id_sondage": object._persistence_idSondage_vh.row['proposition_sondage.id_sondage'],
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
      subject: "You answered at one Survey",
      text: "You answered the question :" + object.libelle
    });
  },
  submitSurvey: function (object) {
    var url = "com.surveymeeting.entity.sondage/insert";
    var inserter = {};
    inserter.propositionSondage = [];
    inserter.inviteSondage = [];
    inserter["libelle"] = object.libelle;
    inserter["lieu"] = object.lieu;
    inserter["description"] = object.description;
    inserter["pseudo"] = "Anonymous";
    inserter["mail_utilisateur"] = object.email;
    inserter["debut"] = ""//new Date();
    inserter["fin"] = ""//object.EndDate;

    _.each(object.answer, function (res) {
      var sousObjReponse = {};
      sousObjReponse["libelle"] = res;
      sousObjReponse["nbr_reponse"] = "0";
      inserter.propositionSondage.push(sousObjReponse);
    });
    _.each(object.contacts, function (contact) {
      var sousObjContact = {};
      sousObjContact["mail_utilisateur"] = contact;
      inserter.inviteSondage.push(sousObjContact);
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
  deleteSurvey: function (object) {
    console.log("deleteSurvey", object);
    var errorstack = 'Survey has been deleted';
    if (object.email === object.info.mailUtilisateur) {
      try {
        var url = "com.surveymeeting.entity.sondage/" + object.info.idSondage;
        HTTP.del(URL + url);
      } catch (error) {
        console.log(error);
        errorstack = "Something went wrong, we apologize for the inconvenient";
        throw new Meteor.Error("An error occured",
          "Something went wrong, we apologize for the inconvenient");
      }
    } else {
      throw new Meteor.Error("Not owner of the survey",
        "You are not allowed to execute this action, you are not the owner of this survey");
    }
    return errorstack;
  },
});
