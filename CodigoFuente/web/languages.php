<?php
// NOTA: para los idiomas también mirar el init.php
$valid_langs = array('en','es','ca');
?>
           <ul class="nav pull-right">
            <li class="divider-vertical .pull-right"></li>
             <li><a href="<?php echo enlaceidioma($valid_langs,'en',ENABLE_LOCAL_WEB);?>"><img src="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/flags/en.png" title="English" alt="English" /> English </a></li>
             <li><a href="<?php echo enlaceidioma($valid_langs,'es',ENABLE_LOCAL_WEB);?>"><img src="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/flags/es.png" title="Español" alt="Español" /> Español </a></li>
             <li><a href="<?php echo enlaceidioma($valid_langs,'ca',ENABLE_LOCAL_WEB);?>"><img src="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/flags/catalonia.png" title="Català" alt="Català" /> Català </a></li>
           </ul>