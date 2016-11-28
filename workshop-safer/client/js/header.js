Template.header.events({
    "click [id^=flag]"(event, instance) {
        defineLanguage(_.last(event.currentTarget.id.split('-')));
    }
})