Router.route('/', {
    name: "crawler"
});

Router.route('/documentation', {
    name: "documentation"
});

Router.route('/settings', {
    name: "settings"
});

Router.route('/userprofile/:id', function () {
    // We set the currentId 
    // Witch is a single Tweet
    Session.set('currentId', this.params.id);
    this.render('userprofile');
});