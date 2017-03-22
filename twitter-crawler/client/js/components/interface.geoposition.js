Template.geoposition.helpers({
    position() {
        Meteor.call('getPositionFromCity', 'California', function (error, result) {
            console.log(error || result);
        });
    }
});