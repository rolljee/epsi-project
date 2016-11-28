// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
// 'starter.controllers' is found in controllers.js
angular.module('starter', ['ionic',
                           'ionic.cloud',
                           'starter.controllers',
                           'starter.services',
                           'ngCordova'])

.run(function($ionicPlatform, $rootScope, $state, LocalStorage) {
  $ionicPlatform.ready(function() {
    $rootScope.userId = LocalStorage.getUserId();
    // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
    // for form inputs)
    if (window.cordova && window.cordova.plugins.Keyboard) {
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);
      cordova.plugins.Keyboard.disableScroll(true);
    }
    if (window.StatusBar) {
      // org.apache.cordova.statusbar required
      StatusBar.styleDefault();
    }

    if (_.isNull($rootScope.userId)) {
      $state.go('login');
    }
  })
})

.config(function($httpProvider, $stateProvider, $urlRouterProvider, $ionicCloudProvider) {
  $ionicCloudProvider.init({
    "core": {
      "app_id": "1:558297579467:android:99c1d14f35dbe9a2"
    },
    "push": {
      "sender_id": "558297579467",
      "pluginConfig": {
        "ios": {
          "badge": true,
          "sound": true
        },
        "android": {
          "iconColor": "#343434"
        }
      }
    }
  })

  $stateProvider
    .state('app', {
      url: '/app',
      abstract: true,
      templateUrl: 'templates/menu.html',
      controller: 'SafeCtrl',
      controllerAs: 'vm'
    })

    .state('login', {
      url: '/login',

          templateUrl: 'templates/login.tpl.html',
          controller: 'loginCtrl',
          controllerAs: 'vm'

    })

    .state('app.profile', {
        url: '/profile',
        views: {
          'menuContent': {
            templateUrl: 'templates/profile.tpl.html',
            controller: 'ProfileCtrl',
            controllerAs: 'vm'
          }
        }
      })

    .state('app.editProfile', {
        url: '/edit-profile',
        views: {
          'menuContent': {
            templateUrl: 'templates/editProfile.tpl.html',
            controller: 'ProfileCtrl',
            controllerAs: 'vm'
          }
        }
      })

    .state('app.playlists', {
      url: '/playlists',
      views: {
        'menuContent': {
          templateUrl: 'templates/playlists.html',
          controller: 'SafeCtrl',
          controllerAs: 'vm'
        }
      }
    });
  $urlRouterProvider.otherwise('/app/profile');
});
