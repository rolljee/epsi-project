Meteor.startup(() => {
    //callHttp();
});

var callHttp = function () {
    // New York, NY lat : 40.6974034 long : -74.1197633
    HTTP.call("POST", 'http://localhost:3000/methods/getTweetListFromLatLong', {
        data: {
            lat: "40.7128",
            long: "74.0059"
        }
    }, function (error, result) {
        console.log(error || result);
    })
}