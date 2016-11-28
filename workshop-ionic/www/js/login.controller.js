angular
  .module('starter.controllers', [])
  .controller('loginCtrl', function($scope, $http, $ionicModal, $ionicPush, LocalStorage, $state) {
    var vm = this;

    vm.loginData = {}
    vm.newUser = {
      token: null
    }

    $ionicModal.fromTemplateUrl('templates/createAccount.tpl.html', {
      scope: $scope, animation: 'slide-in-up'
    }).then(function (modal) {
      $scope.modal = modal;
    });

    $scope.$on('$destroy', function() {
      $scope.modal.remove();
    });

    vm.openModal = function() {
      $scope.modal.show();
    };

    vm.closeModal = function() {
      $scope.modal.hide();
    };

    vm.logIn = function(loginData) {
      var url = 'https://safer.herokuapp.com/api/userconnection';
      var header = {
        'Content-Type': "application/json"
      }

      $http.post(url, loginData, {headers: header})
        .then(function(id) {
          console.log(id)
          LocalStorage.saveUserId(id.data._id);
          $state.go('app.profile');
        }, function(err) {
          alert(err.errorMessage)
        })
    }

    vm.signIn = function() {
      var url = 'https://safer.herokuapp.com/api/newuser';
      var header = {
        'Content-Type': "application/json"
      }

      $ionicPush.register()
        .then(function (t) {
          return $ionicPush.saveToken(t);
        }, function (err) {
          console.log(err)
        })
        .then(function (t) {
          vm.newUser.token = t.token;
          $http.post(url, vm.newUser, {headers: header})
            .then(function(id) {
              LocalStorage.saveUserId(id.data);
              console.log('user created')
            }, function(err) {
               alert(err.errorMessage)
            })
            .finally(function() {
              $state.go('app.profile');
            })
        });
    }

    vm.logOut = function() {
      LocalStorage.saveUserId(null);
      $state.go('login')
    }

  })
