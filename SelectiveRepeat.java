import java.util.Random;
class SelectiveRepeat {
    private static final int WINDOW_SIZE = 4;
    private static final int TOTAL_FRAMES = 10;
    private static final Random rand = new Random();
    private static final boolean[] received = new boolean[TOTAL_FRAMES];
    public static void main(String[] args) {
        int base = 0;
        while (base < TOTAL_FRAMES) {
            System.out.println("\nSender Window: [" + base + " - " + Math.min(base + WINDOW_SIZE - 1, TOTAL_FRAMES - 1) + "]");
            for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
                if (!received[i]) {
                    System.out.println("Sending frame: " + i);
                }
            }
            for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
                if (!received[i]) {
                    if (rand.nextInt(10) < 3) {
                        System.out.println("Frame " + i + " lost!");
                    } else {
                        received[i] = true;
                        System.out.println("Received frame: " + i + " (ACK sent)");
                    }
                }
            }
            while (base < TOTAL_FRAMES && received[base]) {
                base++;
            }
        }
        System.out.println("\nAll frames sent successfully!");
    }
}
