angular
  .module('starter.controllers')
  .controller('ProfileCtrl', function($scope, $rootScope, $http, $ionicModal, $state, LocalStorage, $cordovaSms) {
    var vm = this;
    vm.user = null;

    vm.ice = {}
    vm.patho = {
      name: null,
      medications: []
    }
    vm.medication = {
      name: '',
      start: '',
      end: '',
      posology: '',
      weight: ''
    }
    vm.aller = {
      name: null,
      gravity: null
    }
    vm.back = {
      name: null,
      medications: []
    }
    vm.pract = {}

     vm._init = function() {
      $http({
        method: 'GET', url: 'https://safer.herokuapp.com/api/fiches/h4Xej6JSiHma7zgjM'// + LocalStorage.getUserId()   // zgTi2e2Sq98MmtH9E
      })
        .then(function successCallback(response) {
          vm.user = response.data;
          console.log(response.data)
        }, function errorCallback(response) {
          console.log('Impossible de récupérer le profil utilisateur.')
        })
        .finally(function() {
          $scope.$broadcast('scroll.refreshComplete');
        })

      $ionicModal.fromTemplateUrl('templates/editCategory.tpl.html', {
        scope: $scope, animation: 'slide-in-up'
      }).then(function (modal) {
        $scope.modal = modal;
      });
    }

    $scope.$on('$destroy', function() {
      $scope.modal.remove();
    });

    vm.openModal = function(category) {
      $scope.category = category;
      $scope.modal.show();
      console.log($scope.category)
    };

    vm.closeModal = function() {
      $scope.modal.hide();
    };

    vm.addIce = function(ice) {
      vm.user.ICE.push(ice);
      vm.closeModal();
      vm.ice = null;
    }
    vm.removeIce = function(el) {
      vm.user.ICE.splice(_.indexOf(vm.user.ICE, _.find(vm.user.ICE, { 'name': el.name })), 1);
    }

    vm.addPatho = function(patho) {
      vm.user.pathology.push(patho);
      vm.closeModal();
      vm.patho = null;
    }
    vm.addPathoMedication = function() {
      vm.patho.medications.push(vm.medication);
    }
    vm.removePatho = function(el) {
      vm.user.pathology.splice(_.indexOf(vm.user.pathology, _.find(vm.user.pathology, { 'name': el.name })), 1);
    }

    vm.addAller = function(aller) {
      vm.user.allergies.push(aller);
      vm.closeModal();
      vm.aller = null;
    }
    vm.removeAller = function(el) {
      vm.user.allergies.splice(_.indexOf(vm.user.allergies, _.find(vm.user.allergies, { 'name': el.name })), 1);
    }

    vm.addBack = function(back) {
      vm.user.background.push(back);
      vm.closeModal();
      vm.back = null;
    }
    vm.removeBack = function(el) {
      vm.user.background.splice(_.indexOf(vm.user.background, _.find(vm.user.background, { 'name': el.name })), 1);
    }

    vm.addBackMedication = function() {
      vm.back.medications.push(vm.medication);
    }

    vm.saveProfile = function(user) {
      var url = 'https://safer.herokuapp.com/api/updateInfo';
       var header = {
          'Content-Type': "application/json"
       }
       $http.post(url, user, {headers: header})
        .then(function(file) {

          $state.go('app.profile', {}, { reload: true })
        }, function(err) {
          console.log('Mise à jour impossible')
        })
    }

    vm.sendSms = function () {
      console.log('called')
      $cordovaSms
        .send('0621582665', 'SAFE. \n Je viens d\'avoir un accident. \n Voici ma fiche: https://safer.herokuapp.com/fiche/zgTi2e2Sq98MmtH9E')
        .then(function () {
          console.log('Sms sent')
        }, function (error) {
          console.log('error : ' + error)
        });
      }

    vm._init();
  });
