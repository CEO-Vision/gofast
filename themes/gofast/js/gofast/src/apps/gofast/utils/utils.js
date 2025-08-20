export function getCookies() {
  const cookies = document.cookie.split(';');
  const cookieObject = {};

  cookies.forEach((cookie) => {
    let [key, value] = cookie.split('=');
    key = key.trim(); // Supprimer les espaces autour de la clé
    if (value) {
      value = value.trim(); // Supprimer les espaces autour de la valeur
    }
    cookieObject[key] = value;
  });

  return cookieObject;
}

export function getCurrentLanguage() {
  const urlParams = new URLSearchParams(window.location.search);
  const langParam = urlParams.get('language');
  const cookies = getCookies();
  return langParam || cookies.gofast_user_lang;
}

export function getCurrentUser() {
  const cookies = getCookies();
  return cookies.gofast_user;
}

const Drupal = window.Drupal
export { Drupal };
