package com.phunware;

/**
 * Created by kevinwinegardner on 10/25/16.
 */

import java.lang.reflect.Type;
import java.util.HashMap;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;

public class utils {
    private static final Gson gson = new GsonBuilder().disableHtmlEscaping().create();
    private static final Type TT_hashmapStringString = new TypeToken<HashMap<String,String>>(){}.getType();

    public static String serialize(HashMap<String, Object> map) {
        if (map == null)
            map = new HashMap<String, Object>();
        return gson.toJson(map);
    }

    public static HashMap<String, String> deserialize(String json) {
        if (json == null || json.isEmpty())
            return new HashMap<String, String>();

        return gson.fromJson(json, TT_hashmapStringString);
    }
}
