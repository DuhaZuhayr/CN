import java.util.Random;
class GoBackN {
    private static final int WINDOW_SIZE = 4;
    private static final int TOTAL_FRAMES = 10;
    private static final Random rand = new Random();
    public static void main(String[] args) {
        int base = 0;
        while (base < TOTAL_FRAMES) {
            System.out.println("\nSender Window: [" + base + " - " + Math.min(base + WINDOW_SIZE - 1, TOTAL_FRAMES - 1) + "]");
            for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
                System.out.println("Sending frame: " + i);
            }
            int lostFrame = rand.nextInt(10) < 3 ? base + rand.nextInt(WINDOW_SIZE) : -1;
            for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
                if (i == lostFrame) {
                    System.out.println("Frame " + i + " lost!");
                    break;
                } else {
                    System.out.println("Received frame: " + i);
                }
            }
            if (lostFrame != -1) {
                System.out.println("Timeout! Retransmitting from frame " + lostFrame);
                base = lostFrame;
            } else {
                base += WINDOW_SIZE;
            }
        }
        System.out.println("\nAll frames sent successfully!");
    }
}
