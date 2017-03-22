import { Meteor } from 'meteor/meteor';
import OAuth from 'oauth';
import Twitter from 'twitter'
import Future from 'fibers/future';

var stream;
var client = new Twitter({
    consumer_key: 'nope',
    consumer_secret: 'nope',
    access_token_key: "nope",
    access_token_secret: 'nope'
});

Meteor.methods({
    launchStream(info) {
        check(info, Object);
        check(info.hashtag, String);
        if (_.isEmpty(info.hashtag) === false) {
            stream = client.stream('statuses/filter', { track: info.hashtag });
            stream.on('data', Meteor.bindEnvironment(function (event) {
                _.extend(event, { createdAt: new Date(), relatedHastag: info.hashtag });
                Tweets.insert(event);
            }));
        } else {
            throw new Meteor.Error("Empty value", "Hastag is empty bro !");
        }
    },
    stopStream() {
        stream.destroy();
    },
    reset() {
        Tweets.remove({});
    }
})
