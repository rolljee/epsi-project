Meteor.methods({
    getPositionFromCity(city) {
        try {
            // Get aldeed geoposition
            var geo = new GeoCoder();
            return geo.geocode(city);
        } catch (error) {
            throw new Meteor.Error('Error', error);
        }
    },
    getTweetListFromCityName(city) {
        // Check if all data are correct
        check(city, String);

        // Find out in our tweets if we got the city
        var tweets = Tweets.find({ 'user.location': city }).fetch()
        if (tweets.length > 0) {
            return tweets;
        }
        throw new Meteor.Error('[404] Not found', 'Tweets not found with the given city');
    },
    getTweetListFromLatLong(element) {
        try {
            // Check if all data are correct
            check(element, Object);
            check(element.lat, String);
            check(element.long, String);

            // Get aldeed geoposition
            var geo = new GeoCoder();
            var result = geo.reverse(element.lat, element.long)

            // Find out in our tweets if we got the city
            var tweets = Tweets.find({ 'user.location': result[0].city }).fetch();
            if (tweets.length > 0) {
                var objectReturned = {
                    cityInvolve: result,
                    count: tweets.length,
                    tweets: tweets
                }
                return objectReturned;
            } else {
                throw new Meteor.Error('[404]', 'Tweets not found with the given city');
            }
        } catch (error) {
            throw new Meteor.Error('Error', error);
        }
    },
    getTweetListFromLatLongAndHashtag(element) {
        try {
            // Check if all data are correct
            check(element, Object);
            check(element.lat, String);
            check(element.long, String);
            check(element.relatedHashtag, String);

            // Get aldeed geoposition
            var geo = new GeoCoder();
            var result = geo.reverse(element.lat, element.long)

            // Find out in our tweets if we got the city
            var tweets = Tweets.find({ 'user.location': result[0].city, relatedHashtag: element.relatedHashtag }).fetch();
            if (tweets.length > 0) {
                var objectReturned = {
                    cityInvolve: result,
                    count: tweets.length,
                    relatedHashtag: element.relatedHashtag,
                    tweets: tweets
                }
                return objectReturned;
            } else {
                throw new Meteor.Error('[404]', 'Tweets not found with the given city');
            }
        } catch (error) {
            throw new Meteor.Error('Error', error);
        }
    }
});