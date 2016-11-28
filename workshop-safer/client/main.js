Meteor.startup(function () {
    GoogleMaps.load({ v: '3', key: 'AIzaSyAvH9_o5nGWHJv8mMKo4CYeEVWsVKsqOIw', libraries: 'geometry,places' });
    GoogleMaps.ready('exampleMap', function (map) {
        var marker = new google.maps.Marker({
            position: map.options.center,
            map: map.instance
        });
    });

    GoogleMaps.ready('exampleMapMobile', function (map) {
        var marker = new google.maps.Marker({
            position: map.options.center,
            map: map.instance
        });
    });
    defineLanguage('fr');
    Session.set('actualWidth', document.body.clientWidth);

    Template.main.events({
        'submit #find-fiche'(event, instance) {
            var ficheId = instance.find("#fiche").value;
            if (ficheId.length > 0) {
                $('.mainPage').addClass('animated zoomOutLeft').one('webkitAnimationEnd mozAnimationEnd MSAnimationEnd oanimationend animationend', function () {
                    $('#find-fiche').removeClass('animated zoomOutLeft');
                    Router.go(`/fiche/${ficheId}`);
                });
            } else {
                Session.set('notfound', true);
                $('#find-fiche').addClass('animated shake').one('webkitAnimationEnd mozAnimationEnd MSAnimationEnd oanimationend animationend', function () {
                    $('#find-fiche').removeClass('animated shake');
                    Meteor.setTimeout(function () {
                        Session.set('notfound', false);
                    }, 5000)
                });
            }
            return false;
        }
    });
});
