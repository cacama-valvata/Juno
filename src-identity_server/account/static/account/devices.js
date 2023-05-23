const btns = document.getElementsByClassName ("makedefaultbtn");
Array.from(btns).forEach(button => {
    button.addEventListener ("click", event => {
        key = event.currentTarget.dataset.key;
        key_selector = document.getElementById ('makedefault-selector');
        key_form = document.getElementById ('makedefault-form');

        key_selector.value = key;
        key_form.submit();
    });
});
