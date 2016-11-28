angular
  .module('starter.controllers')

  .controller('SafeCtrl', function ($scope, $rootScope, $ionicPlatform, $cordovaDeviceMotion, $cordovaGeolocation, $cordovaSms, $timeout, $ionicPush, $http) {
    var vm = this;
    vm.accidentDetected = false;

    $ionicPlatform.ready(function () {

      // Listen push notif DONT REMOVE
      $scope.$on('cloud:push:notification', function (event, data) {
        var msg = data.message;
        alert(msg.title + ': ' + msg.text);
      });

      vm.sendSms = function () {
        $cordovaSms
          .send('0621582665', 'SAFE. \n Urgence : Nous avons détecté un choc inquiétant à propos de cet utilisateur. \n Voici sa fiche: https://safer.herokuapp.com/fiche/zgTi2e2Sq98MmtH9E')
          .then(function () {
            console.log('Sms sent')
            vm.accidentDetected = false;
          }, function (error) {
            console.log('error : ' + error)
          });
      }

      vm.sendPush = function () {
         var header = {
           'Content-Type': "application/json"
         }
         var url = 'https://safer.herokuapp.com/api/pushNotification';

         $http.post(url, { email: 'demo@safe.fr' }, { headers: header })
           .then(function() {
             $timeout(vm.sendSms, 8000)
           })
       }

      // Watch Accelerometer
      var options = { frequency: 200 };
      var watch = $cordovaDeviceMotion.watchAcceleration(options);
      watch.then(null, function (error) {
        // An error occurred
      }, function (result) {

        if (vm.accidentDetected === false)
          vm.detectImpac(result);

      });
      })

      vm.directionEnum = {
          Forward : 0,
          Backward : 1,
          FromRight : 2,
          FromLeft : 3
      }

      vm.phoneSideEnum = {
          ScreenSide : 0,
          BackSide : 1
      }

      vm.tiltSideEnum = {
          TopUp : 0,
          BottomUp : 1
      }

      const g = 9.81;
      const multiplier = 500;
      const speedMultiplier = 3.6;
      const interval = 500;
      const mass = 0.155;
      
      var dataArray = [];
      var gravity = [0, 0, 0];
      var speedms = 0;

      vm.detectImpac = function(result) {

          // Get value from Accelerometer
          var x = result.x;
          x = x.toFixed(5);
          var y = result.y;
          y = y.toFixed(5);
          var z = result.z;
          z = z.toFixed(5);
          var timeStamp = result.timestamp;
          // ==================================
          if (dataArray.length > 20) {
              dataArray.pop();
          }

          gravity[0] = g * gravity[0] + (1 - g) * x;
          gravity[1] = g * gravity[1] + (1 - g) * y;
          gravity[2] = g * gravity[2] + (1 - g) * z;

          var xAccel = (x - gravity[0]);// * 100;
          var yAccel = (y - gravity[1]);// * 100;
          var zAccel = (z - gravity[2]);// * 100;

          var gforce = ((Math.abs(x) / g) + (Math.abs(y) / g) + (Math.abs(z) / g));
          //var gforce = Math.sqrt(x * x + y * y + z * z) / 100;
          //var gforce = Math.sqrt(xAccel * xAccel + yAccel * yAccel + zAccel * zAccel) / 10;
          var oldforce = Math.sqrt(x * x + y * y + z * z) / 10;

          
          var nforce = (mass * multiplier) * gforce * g;
          var accel = gforce * g;
          var phoneSide = z > 0 ? vm.phoneSideEnum.ScreenSide : vm.phoneSideEnum.BackSide;
          var tiltSide = y > 0 ? vm.tiltSideEnum.TopUp : vm.tiltSideEnum.BottomUp;
          var fwdAccel = undefined;
          var xAccelDirection = undefined;
          var yAccelDirection = undefined;

          if (tiltSide === vm.tiltSideEnum.TopUp) {
            // Calculate xAccelDirection
            if (xAccel > 0) {
              xAccelDirection = vm.directionEnum.FromLeft;
            } else {
              xAccelDirection = vm.directionEnum.FromRight;
            }
            // Calculate yAccelDirection
            if (yAccel > 0) {
              yAccelDirection = vm.directionEnum.Backward;
            } else {
              yAccelDirection = vm.directionEnum.Forward;
            }

          } else if (tiltSide === vm.tiltSideEnum.BottomUp) {
            // Calculate xAccelDirection
            if (xAccel > 0) {
              xAccelDirection = vm.directionEnum.FromRight;
            } else {
              xAccelDirection = vm.directionEnum.FromLeft;
            }
            // Calculate yAccelDirection
            if (yAccel > 0) {
              yAccelDirection = vm.directionEnum.Forward;
            } else {
              yAccelDirection = vm.directionEnum.Backward;
            }
          }
          
          // if (gforce > 2) {
          //   console.log("============================");
          //   if (gforce > 4) {
          //     console.log("gforce = " + gforce);
          //     console.log("oldforce = " + oldforce);
          //     console.log("xAccelDirection = " + xAccelDirection); 
          //     console.log("yAccelDirection = " + yAccelDirection);
          //     console.log("####")
          //   }
          //   console.log("tiltSide = " + tiltSide); 
          //   console.log("phoneSide = " + phoneSide);
          // }

          //if (fwdAccel) {
              //speedms -= gforce * (interval / 1000);
              //speedms -= accel * (interval / 1000);
          //} else {
              //speedms += gforce * (interval / 1000);
              //speedms += accel * (interval / 1000);
          //}
          
          // conversion m/s to km/h
          var speedKmh = speedms * speedMultiplier;

          var data = {};
          data.x = x; 
          data.y = y; 
          data.z = z; 
          data.nforce = nforce.toFixed(2);
          data.gforce = gforce.toFixed(2); 
          data.accel = accel.toFixed(2); 
          data.speedms = speedms.toFixed(2);
          data.speedkmh = speedKmh.toFixed(2);
          //data.fwdAccel = fwdAccel;
          //data.isFalling = (z < 0.2 && z > -0.2) ? true : false; 

          var impactGravity = 1;          

          if (gforce > 5 && vm.accidentDetected == false) {
            if (gforce > 7)
              impactGravity = 2;
            if (gforce > 9)
              impactGravity = 3;

            console.log('ACCIDENT DETECTED');
            vm.accidentDetected = true;
            vm.gravity = impactGravity;
            //console.log('GRAVITY : ' + vm.gravity);
            vm.getLocation();
          }
      }

      // Geolocation
      vm.getLocation = function() {
        var posOptions = { timeout: 10000, enableHighAccuracy: false };
        $cordovaGeolocation
          .getCurrentPosition(posOptions)
          .then(function (position) {
            var url = 'https://safer.herokuapp.com/api/putlocation'
             var header = {
               'Content-Type': "application/json"
             }
            var rayon = 6371
            var lat = position.coords.latitude
            var long = position.coords.longitude
            var coords = {
              lat: lat,
              long: long,
              date: new Date(),
              _id: 'WweHWuj5w4jGrFHG2',
              gravity: vm.gravity
            }
             $http.post(url, coords, {headers: header})
              .then(function() {
                vm.sendPush()
              }, function(err) {
                console.log(err)
              })
          })
        }
  });
