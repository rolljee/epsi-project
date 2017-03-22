Template.navbar.events({
    "click .menubar"(event, instance) {
        $('.menubar').each(function () {
            $(this).removeClass('active');
        })
        $(`#${event.currentTarget.id}`).toggleClass('active');
    }
});