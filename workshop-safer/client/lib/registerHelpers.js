Template.registerHelper('is404', function () {
    return Session.get('is404');
});

Template.registerHelper('notfound', function () {
    return Session.get('notfound');
});