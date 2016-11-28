Meteor.methods({
    encryptData(sequence) {
        var encrypted = CryptoJS.AES.encrypt(sequence, "WithLoveFromSafer");
        return encrypted.toString();
    },
    decryptData(sequence) {
        var decrypted = CryptoJS.AES.decrypt(sequence, "WithLoveFromSafer");
        return decrypted.toString(CryptoJS.enc.Utf8)
    },
    'fiche.findOne'(element) {
        var modifier = {};
        modifier._id = element._id
        element = _.omit(element, '_id');
        _.map(element, function (element, key) {
            if (isArrayOrObject(element)) {
                modifier[key] = iterateAndDecrypt(element);
            } else {
                modifier[key] = Meteor.call('decryptData', element.toString());
            }
        });
        return modifier;
    },
    reverseGeocode(element) {
        var geo = new GeoCoder();
        console.log(geo);
        console.log(element);
        return geo.reverse(element.lat, element.long);
    }
});

isArrayOrObject = function (value) {
    if ((_.isArray(value) || _.isObject(value))) {
        return true;
    }
    return false;
}
iterateAndEncrypt = function (element) {
    if (_.isArray(element)) {
        _.each(element, function (value) {
            if (!_.isArray(value)) {
                _.map(value, function (valueToEncrypt, key) {
                    if (_.isArray(valueToEncrypt)) {
                        iterateAndEncrypt(valueToEncrypt);
                    } else {
                        _.extend(value, { [key]: Meteor.call('encryptData', valueToEncrypt.toString()) })
                    }
                });
            }
        });
    } else {
        _.map(element, function (value, key) {
            _.extend(element, { [key]: Meteor.call('encryptData', value.toString()) });
        })
    }
    return element;
}

iterateAndDecrypt = function (element) {
    if (_.isArray(element)) {
        _.each(element, function (value) {
            if (!_.isArray(value)) {
                _.map(value, function (valueToDecrypt, key) {
                    if (_.isArray(valueToDecrypt)) {
                        iterateAndDecrypt(valueToDecrypt);
                    } else {
                        _.extend(value, { [key]: Meteor.call('decryptData', valueToDecrypt.toString()) })
                    }
                });
            }
        });
    } else {
        _.map(element, function (value, key) {
            _.extend(element, { [key]: Meteor.call('decryptData', value.toString()) });
        })
    }
    return element;
}