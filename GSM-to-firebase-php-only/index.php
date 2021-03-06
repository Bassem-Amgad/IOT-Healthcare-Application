<?php

require('../vendor/autoload.php');

use Kreait\Firebase\Factory;
use Kreait\Firebase\ServiceAccount;

// This assumes that you have placed the Firebase credentials in the same directory
// as this PHP file.
$serviceAccount = ServiceAccount::fromJsonFile(__DIR__.'/doctor-4c9a4-firebase-adminsdk-nkppq-51111dc01d.json');

$firebase = (new Factory)
    ->withServiceAccount($serviceAccount)
    // The following line is optional if the project id in your credentials file
    // is identical to the subdomain of your Firebase project. If you need it,
    // make sure to replace the URL with the URL of your project.
    //->withDatabaseUri('https://my-project.firebaseio.com')
    ->create();

$database = $firebase->getDatabase();


$app = new Silex\Application();
$app['debug'] = true;

// Register the monolog logging service
$app->register(new Silex\Provider\MonologServiceProvider(), array(
  'monolog.logfile' => 'php://stderr',
));

// Register view rendering
$app->register(new Silex\Provider\TwigServiceProvider(), array(
    'twig.path' => __DIR__.'/views',
));

// Our web handlers

$app->get('/', function() use($app) {
  $app['monolog']->addDebug('logging output.');
  return $app['twig']->render('index.twig');
});


$app->get('/{ref}/{oxygen}/{pulse}/{temp}/{long}/{lat}/{date}', function($ref,$oxygen,$pulse,$temp,$long,$lat,$date) use($app, $database) {
$newPost = $database
    ->getReference($ref)
    ->update([
      $date =>[
        'readingLatitude' => $lat,
        'readingLongitude' => $long,
        'readingOxygen' => $oxygen,
        'readingPulse' => $pulse,
        'readingTemp' => $temp
        ]
      ]);

// pushing data with a random key: >> success
// $newPost = $database
//     ->getReference($ref)
//     ->set([
//         'Date' => $date,
//         'readingOxygen' => $oxygen,
//         'readingPulse' => $pulse,
//         'readingTemp' => $temp
//     ]);
  
  return json_encode(["msg" => "done"]);
});

$app->run();
