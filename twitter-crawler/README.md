# __Twitter project for Cloud management__

We used Meteor to crawl twitter for a moment and expose an API   
The purpose is to test the power of [Gcloud](https://cloud.google.com/) with Meteor and then punch it with this -> [gatling](http://gatling.io/#/)


# __Getting started with meteor__

Intall Meteor if it's not already done :  
* [Install Meteor](https://www.meteor.com/install)
* `git clone https://github.com/rolljee/twitter-cloud-crawler`
* `cd /path/to/myapp && meteor npm install`
* `meteor`

## __Run mobile app__

`meteor add-platform ios`  

then refer to the [doc](https://www.meteor.com/tutorials/blaze/running-on-mobile) 


## __Run desktop application__

```javascript
"devDependencies": {
    "meteor-desktop": "^0.2.2"
  }  
```
  
Since meteor-desktop was added using meteor npm install and ios platform later on, we should be able to launch our desktop app  

 
Launch Meteor on port 3000 from one term

`cd path/to/myapp/ && meteor --mobile-server 127.0.0.1`

Then in an other terminal :

`npm run desktop -- init` 
`npm run desktop` 

After some installation, your app should launch ( if not refer to the [doc](https://www.npmjs.com/package/meteor-desktop))


# __Fonctionnalités__
## __Routes name__


```javascript
Get all tweets list :
http://localhost:3000/publications/Tweets 


Get specific hashtag from position:
http://localhost:3000/methods/getTweetListFromLatLongAndHashtag

@params
{
  "lat" : "40.7128",  
  "long" : "74.0059",
  "relatedHashtag": "hashtag"
}
  

Get specific tweet from position :
http://localhost:3000/methods/getTweetListFromLatLong
  
@params
{
  "lat" : "40.7128",  
  "long" : "74.0059",
}
 
```
# __Contributors__

Mabileau Clément  
Arnaud Passlaigue  
Riquelme Nicolas (me)