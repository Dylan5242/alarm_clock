import org.json.JSONArray;
import org.json.JSONObject;

import java.io.IOException;
import java.nio.file.*;
import java.time.*;
import java.util.*;

public class AlarmBackground {

    private static final String JSON_PATH = "alarms.json";
    private static final int MAX_WEEKS = 4;

    private static int currentWeek = 1;

    public static void main(String[] args) {
        try {
            Path path = Paths.get(JSON_PATH);
            if (!Files.exists(path)) {
                System.err.println("Файл alarms.json не найден.");
                return;
            }

            // Чтение JSON
            String content = Files.readString(path);
            JSONObject root = new JSONObject(content);

            // Получение массива будильников
            JSONArray alarms = root.optJSONArray("alarms");
            if (alarms == null) return;

            // Получение текущей даты и времени
            LocalDateTime now = LocalDateTime.now();
            String today = now.getDayOfWeek().getDisplayName(java.time.format.TextStyle.SHORT, new Locale("ru")).toLowerCase(Locale.ROOT); // "пн", "вт"...
            String currentTime = String.format("%02d:%02d", now.getHour(), now.getMinute());

            // Определим текущую рабочую неделю
            currentWeek = calculateWeekFromAlarms(alarms);

            boolean matchFound = false;

            for (int i = 0; i < alarms.length(); i++) {
                JSONObject alarm = alarms.getJSONObject(i);

                boolean enabled = alarm.optBoolean("active", false);
                String days = alarm.optString("day", "");
                String time = alarm.optString("time", "");
                int week = alarm.optInt("week", 0);

                if (!enabled || week != currentWeek) continue;
                if (!Arrays.asList(days.split(" ")).contains(today)) continue;
                if (!time.equals(currentTime)) continue;

                matchFound = true;
                break;
            }

            if (matchFound) {
                System.out.println("Найден активный будильник → Устанавливаем alarm_trigger = true");
                root.put("alarm_trigger", true);
                Files.writeString(path, root.toString(2));
                // Запуск GUI-приложения (если нужно):
                // Runtime.getRuntime().exec("название_программы.exe");
            } else {
                System.out.println("⏱ Будильник пока не активен.");
            }

        } catch (IOException e) {
            System.err.println("Ошибка файла: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Ошибка выполнения: " + e.getMessage());
        }
    }

    private static int calculateWeekFromAlarms(JSONArray alarms) {
        int maxWeek = 1;
        for (int i = 0; i < alarms.length(); i++) {
            JSONObject alarm = alarms.getJSONObject(i);
            int week = alarm.optInt("week", 1);
            maxWeek = Math.max(maxWeek, week);
        }

        // Предположим, что у нас есть файл или переменная, где хранится последняя неделя — пока просто симулируем.
        // Можно расширить с сохранением/чтением lastKnownWeek + date.
        LocalDate today = LocalDate.now();
        int base = today.get(WeekFields.ISO.weekOfWeekBasedYear()) % maxWeek;
        return base == 0 ? maxWeek : base;
    }
}
