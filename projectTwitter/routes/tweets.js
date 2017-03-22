/**
 * Copyright 2016, Google, Inc.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

'use strict';

const express = require('express');
const router = express.Router();
const OAuth = require('oauth');
const _ = require('underscore');
const geocoder = require('geocoder');
const MongoClient = require('mongodb').MongoClient;

// [START hello_world]
router.get('/', (req, res) => {
    var url = 'mongodb://safer:root@ds019796.mlab.com:19796/safer';
    MongoClient.connect(url, function (err, db) {
        var data = req.query;
        if (data.lat && data.long) {
            geocoder.reverseGeocode(data.lat, data.long, function (err, result) {
                var addresses = [];
                _.each(result.results[0].address_components, function (address) {
                    addresses.push(address.short_name);
                })
                findTweet(db, { cities: addresses, relatedHashtag: data.relatedHashtag }, function (documents) {
                    console.log(documents);
                    sendResult(documents);
                });
            });

        } else {
            findTweet(db, { relatedHashtag: data.relatedHashtag }, function (documents) {
                sendResult(documents);
            });
        }
    });
    // [END hello_world]

    var findTweet = function (db, data, callback) {
        // Get the documents collection 
        var collection = db.collection('twitter');
        // find some documents 
        console.log(data);
        if (data.relatedHashtag) {
            collection.find({ "entities.hashtags.text": data.relatedHashtag }).toArray(function (err, docs) {
                callback(docs);
            });
        } else {
            collection.find({ 'place.name': { "$in": data.cities } }).toArray(function (err, docs) {
                callback(docs);
            });
        }
    }
    var sendResult = function (documents) {
        if (documents && documents.length > 0) {
            var objectReturned = {
                count: documents.length,
                tweets: documents
            }
            res.send(objectReturned);
        }
        else {
            res.send('No results were found');
        }
    }
});
module.exports = router;