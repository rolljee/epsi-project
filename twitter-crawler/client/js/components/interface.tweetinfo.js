Template.tweetinfo.onCreated(function () {
    Session.set('pagination', 10);
});

Template.tweetinfo.events({
    'click .users'(event, instance) {
        Router.go('/userprofile/' + event.currentTarget.id);
    },
})

Template.tweetinfo.helpers({
    tweets() {
        return Tweets.find({}, { limit: 10, skip: Session.get('pagination') });
    }
});