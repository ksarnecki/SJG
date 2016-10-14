<?php
class DBGenCommon
{
    public static function box($ints)
    {
        $buf = "";
        for ($i = 0; $i < count($ints); $i++)
            $buf = $buf + ($i == 0 ? "" : ",") + $ints[$i];
        return $buf;
    }
    public static function boxs($db, $strs)
    {
        $buf = "";
        for ($i = 0; $i < count($strs); $i++) {
            if ($i != 0) {
                $buf = $buf + ",";
            }
            $buf = $buf + "'";
            $buf = $buf + $db->escape($strs[$i]);
            $buf = $buf + "'";
        }
        return $buf;
    }
    public static function prepare($sql, $pmap)
    {
        foreach ($pmap as $key => $value) {
            $sql = str_replace("%[" . $key . "]", $value, $sql);
        }
        return $sql;
    }
}
?>