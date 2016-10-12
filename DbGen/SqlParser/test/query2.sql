SELECT a.id, a.name, i.file_path, a.url 
   FROM pwh_advert a, pwh_image i 
   WHERE (CASE WHEN a THEN b WHEN a THEN b  ELSE c END)