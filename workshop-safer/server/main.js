import { Meteor } from 'meteor/meteor';


Meteor.startup(() => {
    console.log("Server started");
     //createUser('http://localhost:3000/api/newuser')
    // postNotification('https://api.ionic.io/push/notifications')
    // addFiche('http://localhost:3000/api/addFiche');
    // updatefiche('http://localhost:3000/api/updateInfo');
});


var createUser = function (url) {
    Meteor.defer(function () {
        HTTP.call("POST", url, {
            data: {
                //username: 'username',
                email: 'test1@gmail.com',
                password: "123456",
                token: "e79zKKkSa4o:APA91bFkOztmpGyY4MXGhbIsxp5673GLRRMt4_RBWPj_bR6dZZAKruVCFlk5WjRj_xCWK5HH9gYlrnQGouSSF_wQAHHElZfVn0V_JW1dVPc0zPxUCIan-V83FF-M738vzVfEnSUpiipC"
            }
        });
    });
}

var postNotification = function (url) {
    Meteor.defer(function () {
        HTTP.post(url, {
            data: {
                "tokens": ["e79zKKkSa4o:APA91bFkOztmpGyY4MXGhbIsxp5673GLRRMt4_RBWPj_bR6dZZAKruVCFlk5WjRj_xCWK5HH9gYlrnQGouSSF_wQAHHElZfVn0V_JW1dVPc0zPxUCIan-V83FF-M738vzVfEnSUpiipC"],
                "profile": "safe",
                "notification": {
                    "message": "T'es mort ? le server envoie un push notif"
                }
            },
            headers: {
                'Content-Type': "application/json",
                'Authorization': "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiIyNmI0MGE5YS04ZjUxLTQwZmEtYWMyZC04NGQ1Nzg0YzVkOTUifQ.FIw5R-yq0Pn-KmTPzCGAsaobLK4bTeOyFxsBRXdq_Tg"
            }
        }, function (error, result) {
            if (error) {
                console.log("ERROR", error)
            } else {
                console.log("RESULT", result);
            }
        });
    });
}

var updatefiche = function (url) {
    Meteor.defer(function () {
        console.log('Sending POST request');
        HTTP.post(url, {
            data: {
                "_id": "2BxnGxhD6FDJecmXd",
                "firstname": "fhizufh",
                "lastname": "zziuuzeiug",
                "birth": "08/09/1994",
                "sexe": "M",
                "bloodtype": "O+",
                "weight": 70,
                "height": 175,
                "phone": "0623447277",
                "secu": "194093452156985",
                "ICE": [
                    {
                        "firstname": "Gunilla",
                        "phone": "0615444277",
                        "relationship": "Mother"
                    },
                    {
                        "firstname": "Nicolas",
                        "phone": "0621582665",
                        "relationship": "Brother"
                    }
                ],
                "pathology": [
                    {
                        "name": "Diabétique",
                        "medications": [
                            {
                                "name": "Glucophage",
                                "posology": 3,
                                "weight": 850,
                                "startDate": "10/11/2016",
                                "endDate": "14/11/2016"
                            }
                        ]
                    },
                    {
                        "name": "Trisomique"
                    },
                    {
                        "name": "VIH",
                        "medications": [
                            {
                                "name": "Zidovudine",
                                "posology": 2,
                                "weight": 600,
                                "startDate": "10/11/2016",
                                "endDate": "14/11/2016"
                            },
                            {
                                "name": "rilpivirine",
                                "posology": 1,
                                "weight": 25,
                                "startDate": "10/11/2015",
                                "endStart": "14/11/2017"
                            }
                        ]
                    }
                ],
                "allergies": [
                    {
                        "name": "Pollen",
                        "gravity": "2"
                    },
                    {
                        "name": "latex",
                        "gravity": "5"
                    }
                ],
                "background": [
                    {
                        "name": "Oeudème papillaire",
                        "medications": [
                            {
                                "name": "Cortisone",
                                "posology": 1,
                                "weight": 20,
                                "startDate": "01/01/2015",
                                "endDate": "01/01/2016"
                            }
                        ]
                    }
                ],
                "practitioner": {
                    "firstname": "Stéphane",
                    "lastname": "Dareau",
                    "phone": "0612458525"
                },
                "medicalNote": {
                    "text": "Lorem ipsum dolores ...."
                },
                "organ": true,
                "photo": "data:image/png;base64,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"
            }
        });
    });
}


var addFiche = function (url) {
    Meteor.defer(function () {
        console.log('Sending POST request');
        HTTP.post(url, {
            data: {
                "firstname": "fhizufh",
                "lastname": "zziuuzeiug",
                "birth": "08/09/1994",
                "sexe": "M",
                "bloodtype": "O+",
                "weight": 70,
                "height": 175,
                "phone": "0623447277",
                "secu": "194093452156985",
                "ICE": [
                    {
                        "firstname": "Gunilla",
                        "phone": "0615444277",
                        "relationship": "Mother"
                    },
                    {
                        "firstname": "Nicolas",
                        "phone": "0621582665",
                        "relationship": "Brother"
                    }
                ],
                "pathology": [
                    {
                        "name": "Diabétique",
                        "medications": [
                            {
                                "name": "Glucophage",
                                "posology": 3,
                                "weight": 850,
                                "startDate": "10/11/2016",
                                "endDate": "14/11/2016"
                            }
                        ]
                    },
                    {
                        "name": "Trisomique"
                    },
                    {
                        "name": "VIH",
                        "medications": [
                            {
                                "name": "Zidovudine",
                                "posology": 2,
                                "weight": 600,
                                "startDate": "10/11/2016",
                                "endDate": "14/11/2016"
                            },
                            {
                                "name": "rilpivirine",
                                "posology": 1,
                                "weight": 25,
                                "startDate": "10/11/2015",
                                "endStart": "14/11/2017"
                            }
                        ]
                    }
                ],
                "allergies": [
                    {
                        "name": "Pollen",
                        "gravity": "2"
                    },
                    {
                        "name": "latex",
                        "gravity": "5"
                    }
                ],
                "background": [
                    {
                        "name": "Oeudème papillaire",
                        "medications": [
                            {
                                "name": "Cortisone",
                                "posology": 1,
                                "weight": 20,
                                "startDate": "01/01/2015",
                                "endDate": "01/01/2016"
                            }
                        ]
                    }
                ],
                "practitioner": {
                    "firstname": "Stéphane",
                    "lastname": "Dareau",
                    "phone": "0612458525"
                },
                "medicalNote": {
                    "text": "Lorem ipsum dolores ...."
                },
                "organ": true,
                "photo": "data:image/png;base64,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"
            }
        });
    });
}