Template.userprofile.onCreated(function () {
    this.subscribe('Tweets');
});
Template.userprofile.helpers({
    userId() {
        return Session.get('currentId');
    },
    tweetAffiliated() {
        return Tweets && Tweets.findOne({ _id: Session.get('currentId') });
    }
});