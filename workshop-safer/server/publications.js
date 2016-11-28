Meteor.publish("Fiches", function () {
    return Fiches.find();
});

Meteor.publish("Geolocalisation", function () {
    return Geolocalisation.find();
});