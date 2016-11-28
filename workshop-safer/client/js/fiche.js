Template.fiche.onCreated(function () {
    this.subscribe("Fiches");
    this.subscribe('Geolocalisation');
    Session.set('actualWidth', screen.width);
});

Template.fiche.onRendered(function () {
    var self = this;
    this.$('.mainPage').addClass('animated fadeInRight');
    var file = Fiches.findOne(Session.get('activeFiche'));
    if (typeof file != 'undefined') {
        var result = Meteor.call('fiche.findOne', file, function (error, result) {
            if (!error) {
                Session.set('fiche', result);
            }
        });
    } else {
        Session.set('is404', true);
    }
    $(window).resize(function (evt) {
        var currentWidth = document.body.clientWidth;
        Session.set('actualWidth', currentWidth);
        if (Session.get('actualWidth') >= 768) {
            GoogleMaps.load();
            GoogleMaps.ready('exampleMap', function (map) {
                var marker = new google.maps.Marker({
                    position: map.options.center,
                    map: map.instance
                });
            });
        }
        else if (Session.get('actualWidth') < 768) {
            GoogleMaps.load();
            GoogleMaps.ready('exampleMapMobile', function (map) {
                var marker = new google.maps.Marker({
                    position: map.options.center,
                    map: map.instance
                });
            });
        }
    });
});

Template.fiche.helpers({
    myfiche() {
        return Session.get('fiche');
    },
    exampleMapOptions: function () {
        if (GoogleMaps.loaded()) {
            var loc = Geolocalisation.findOne({ owner: Session.get('fiche')._id }).position;
            if (typeof loc != 'undefined') {
                return {
                    center: new google.maps.LatLng(loc.lat, loc.long),
                    zoom: 15
                };
            } else {
                console.log('Position is not loaded');
            }
        }
    },
    locationMarker() {
        return Geolocalisation.findOne({ owner: Session.get('fiche')._id }) && Geolocalisation.findOne({ owner: Session.get('fiche')._id });
    },
    hideGoogleMap() {
        return Geolocalisation.findOne({ owner: Session.get('fiche')._id }) == undefined ? true : false;
    },
    sexeIcon() {
        return this.sexe === 'M' ? "fa-mars" : "fa-venus";
    },
    warningImg() {
        var gravity = Geolocalisation.findOne({ owner: Session.get('fiche')._id }).gravity;
        if (gravity === '1') {
            return "/img/warningSafe.png";
        } else if (gravity === '2') {
            return "/img/warningMedium.png";
        }
        else if (gravity === '3') {
            return "/img/warningDanger.png";
        }
    },
    currentlocation() {
        var loc = Geolocalisation.findOne({ owner: Session.get('fiche')._id }).position;
        if (typeof loc != 'undefined') {
            Meteor.call('reverseGeocode', { long: loc.long, lat: loc.lat }, function (error, result) {
                Session.set('location', result[0].formattedAddress);
            })
            return Session.get('location');
        } else {
            console.log('Loading address');
        }
    }
});

Template.fiche.events({
    "click .carousel"(event, instance) {
        var id = event.currentTarget.id;
        $.each($(".carousel"), function (idx, value) {
            $(value).removeClass('active');
            if ($(value).prop('id') !== id) {
                $('#div' + $(value).prop('id')).hide('slow');
            }
        });
        $(`#${event.currentTarget.id}`).addClass('active');
        $('#div' + id).show('slow');

    },
    "click #left"(event, instance) {
        let puce = $('.pagination').find('.active').prop('id');
        let prev = $(`#${puce}`).prev('.carousel').prop('id');
        if (prev == undefined) {
            prev = $(`#background`).prop('id');
        }
        $(`#${puce}`).removeClass('active');
        $(`#${prev}`).addClass('active');

        $('#div' + puce).hide('slow');
        $('#div' + prev).show('slow');

    },
    "click #right"(event, instance) {
        let puce = $('.pagination').find('.active').prop('id');
        let next = $(`#${puce}`).next('.carousel').prop('id');
        if (next == undefined) {
            next = $(`#ICE`).prop('id');
        }
        $(`#${puce}`).removeClass('active');
        $(`#${next}`).addClass('active');
        $('#div' + puce).hide('slow');
        $('#div' + next).show('slow');
    }
});
