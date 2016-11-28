import { Meteor } from 'meteor/meteor';


Meteor.startup(() => {
  process.env.MAIL_URL = "smtp://postmaster%40sandbox5ad46ba86a2b4eea966b8121f18e17d1.mailgun.org:da82c19d2104b4dc7baad0ba41aa5e20@smtp.mailgun.org:587";
});
