Meteor.publish('Tweets', function () {
    return Tweets.find({});
});