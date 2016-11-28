angular.module('starter.services', [])
  .factory('LocalStorage', function LocalStorage() {
    var Storage = {};

    Storage.initLocalStorage = function () {

    };

    Storage.saveUserId = function (params) {
      localStorage.setItem("safe-id", JSON.stringify(params));
    };

    Storage.getUserId = function () {
      return JSON.parse(localStorage.getItem("safe-id"));
    };

    return Storage;
  });
