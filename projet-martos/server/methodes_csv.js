import fs from 'fs';
import json2csv from 'json2csv';
import json2xls from 'json2xls';
import path from 'path';

Meteor.methods({
    sendcsv: function (object) {
        var attachment = {};
        var basename = "survey-meeting.xlsx";
        var directory = "D:\\";
        var _path = path.normalize(path.join(directory, basename));
        var formatedObject = {};

        if (object.isSurvey) {

            formatedObject.reponseSondage = [];
            formatedObject.invite = [];

            formatedObject.libelle = object.info.libelle;
            formatedObject.description = object.info.description;
            formatedObject.debut = object.info.debut;
            formatedObject.fin = object.info.fin;
            _.each(object.info.reponseSondageCollection, function (reponse) {
                _.each(object.info.propositionSondageCollection, function (proposition) {
                    console.log(reponse.reponseSondagePK.idProposition);
                    if (reponse.reponseSondagePK.idProposition === proposition.idProposition) {
                        formatedObject.reponseSondage.push(proposition.libelle);
                    }
                });
            });

            _.each(object.info.inviteSondageCollection, function (invite) {
                formatedObject.invite.push(invite.inviteSondagePK.mailUtilisateur);
            });

            console.log(JSON.stringify(formatedObject));

        } else if (object.isMeeting) {
            
            formatedObject.reponseMeeting = [];
            formatedObject.invite = [];

            formatedObject.libelle = object.info.libelle;
            formatedObject.description = object.info.description;
            formatedObject.debut = object.info.debut;
            formatedObject.fin = object.info.fin;
            _.each(object.info.reponseRdvCollection, function (reponse) {
                _.each(object.info.propositionRdvCollection, function (proposition) {
                    if (reponse.reponseRdvPK.idProposition === proposition.idProposition) {
                        formatedObject.reponseMeeting.push(proposition.heureDebut + "-" + proposition.heureFin);
                    }
                });
            });

            _.each(object.info.inviteRdvCollection, function (invite) {
                formatedObject.invite.push(invite.inviteRdvPK.mailUtilisateur);
            });

            console.log(JSON.stringify(formatedObject));
        } else {
            throw new Meteor.Error("An error occured",
                "Something went wrong, we apologize for the inconvenient");
        }

        var xls = json2xls(formatedObject);
        try {
            console.log(_path);
            fs.writeFileSync(_path, xls, 'binary');

            attachment.fileName = basename;
            attachment.filePath = directory + basename;
            console.log("attachment : ", attachment);

            Email.send({
                to: "n.riquelmebareiro@gmail.com",
                from: "no-reply@surveymeeting.com",
                subject: "You asked for the xls file",
                attachments: [attachment],
                text: "As asked, you will find in attachment the file you are looking for !"
            });
        } catch (error) {
            throw new Meteor.Error("An error occured",
                "Something went wrong, we apologize for the inconvenient");
        }
    }
});