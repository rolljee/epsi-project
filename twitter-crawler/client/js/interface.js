Template.tweet.onRendered(function() {
    $('#scrollme').scrollTop($('#scrollme')[0].scrollHeight + 1000);
    //Session.set('limiter', Session.get('limiter') + 20);
});

Template.interface.onCreated(function() {
    this.subscribe('Tweets');
    Session.set('limiter', 50);
});

Template.interface.helpers({
    tweets() {
        return Tweets.find({}, { limit: Session.get('limiter'), sort: { createdAt: -1 } });
    },
    total() {
        return Tweets.find().count()
    },
    screenHeight() {
        return $(window).height() - 150;
    },
    currentStream() {
        return Session.get('currentStream');
    }
});

Template.interface.events({
    'submit #start'(event, instance) {

        // Will first kill the current stream
        Meteor.call('stopStream');

        // Then we launch the new one
        Session.set('currentStream', instance.find('#hashtag-value').value);
        Meteor.call('launchStream', { hashtag: instance.find('#hashtag-value').value }, function(error, result) {
            if (error) {
                sAlert.error(`An error happened : ${error}`);
            } else {
                sAlert.success(`Starting the stream`);
            }
        });
        return false; // So we avoid the re rendering of the windows
    },
    'click #stop'(event, instance) {
        Meteor.call('stopStream', function(error, result) {
            if (error) {
                sAlert.error(`An error happened : ${error.message}`);
            } else {
                Session.set('currentStream', '');
                sAlert.success(`Stream has been stopped succesfully`);
            }
        });
    },
    'click .menu'(event, instance) {
        // Toggle right menu
        var template = event.currentTarget.id;
        $('.display-class').hide();
        $(`.${template}`).toggle('slow');
    },
    'click #old'(event, instance) {
        // Go left
        Session.set('pagination', Session.get('pagination') - 10);
    },
    'click #next'(event, instance) {
        // Go right 
        Session.set('pagination', Session.get('pagination') + 10);
    },
    'click #reset'(event, instance) {
        // Reset all the current tweets
        Meteor.call('reset');
    }
});

Template.tweet.helpers({
    isLink() {
        return Spacebars.SafeString(urlify(this.text));
    }
});