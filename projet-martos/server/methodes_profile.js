import { HTTP } from 'meteor/http';
import { Meteor } from 'meteor/meteor';
Meteor.methods({
	forgotpassword: function (string_email) {
		var bool = checkMailFormat(string_email);
		if (bool) {
			const url = 'com.surveymeeting.entity.utilisateur/mail=';
			const final_url = URL + url + string_email;
			try {
				var back = HTTP.get(final_url);
				if (!_.isEmpty(back.data)) {
					Email.send({
						to: "n.riquelmebareiro@gmail.com",//object.email,
						from: "no-reply@surveymeeting.com",
						subject: "You asked to get your password",
						text: `Account : ${string_email}, password is ${back.data.password}`
					});
				}
			} catch (error) {
				throw new Meteor.Error("An error occured",
					"User not found");
			}
		} else {
			throw new Meteor.Error("Wrong email format",
				"Wrong email format");
		}
	},
	logMeIn: function (object) {
		var toReturn = {};
		const url = 'com.surveymeeting.entity.utilisateur/mail=';
		const final_url = URL + url + object.email + "&&password=" + object.password;
		try {
			var back = HTTP.get(final_url);
			if (!_.isEmpty(back.data)) {
				toReturn.idUtilisateur = back.data.idUtilisateur;
				toReturn.mail = back.data.mail;
				toReturn.prenom = back.data.prenom;
			}
		} catch (error) {
			throw new Meteor.Error("An error occured",
				"User not found");
		}
		return toReturn;
	},
	createAccount: function (object) {
		const url = 'com.surveymeeting.entity.utilisateur/mail=';
		const final_url = URL + url + object.email;
		var back;
		try {
			var result = HTTP.call("POST", URL + "com.surveymeeting.entity.utilisateur/", {
				data: {
					"mail": object.email,
					"nom": object.lastname,
					"password": object.password,
					"prenom": object.firstname
				},
				headers: { "content-type": "application/json" }
			});
		} catch (error) {
			throw new Meteor.Error("An error occured",
				JSON.stringify(error));
		}
	},
	changepassword: function (object) {
		console.log(object);
		if (object.newpassword === object.confirmnewpassword && object.newpassword !== object.oldpassword) {
			var result = HTTP.call("PUT", URL + "com.surveymeeting.entity.utilisateur/" + object._id, {
				data: {
					"password": object.newpassword,
				},
				headers: { "content-type": "application/json" }
			}, function (error, result) {
				console.log(result);
			});
		} else {
			throw new Meteor.Error("An error occured",
				"Both password are different, please try again.");
		}

	},
	changeEmail: function (object) {
		var check = checkMailFormat(object.newEmail);
		console.log("check : ", check);
		if (check) {
			var result = HTTP.call("POST", URL + "com.surveymeeting.entity.utilisateur/" + object._id, {
				data: {
					"mail": object.newEmail,
				},
				headers: { "content-type": "application/json" }
			}, function (error, result) {
				if (err) {
					throw new Meteor.Error("An error occured",
						"An error occured while modifying the email, we apologise for the inconvenient");
				}
			});
		} else {
			throw new Meteor.Error("An error occured",
				"Email format is not valid");
		}

	},
	addToContactList: function (object) {
		if (!_.isEmpty(object.emailcontact)) {
			Contact.update({ owner: object.emailOwner }, { $push: { contact: object.emailcontact } }, { upsert: true });
		} else {
			throw new Meteor.Error("Empty email",
				"You can't add an empty value, please fill every field before submit an new contact");
		}
	},
	removeContact: function (object) {
		Contact.update({ owner: object.emailOwner }, { $pull: { contact: object.emailcontact } }, { upsert: true });
	}
});



checkMailFormat = function (email) {
	var reg = new RegExp('^[a-z0-9]+([_|\.|-]{1}[a-z0-9]+)*@[a-z0-9]+([_|\.|-]{1}[a-z0-9]+)*[\.]{1}[a-z]{2,6}$', 'i');
	if (reg.test(email)) {
		console.log("true");
		return true;
	}
	else {
		console.log("false");
		return false;
	}
}