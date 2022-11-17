package panyi.xyz.textrender;

public final class NativeBridge {
    // Used to load the 'textrender' library on application startup.
    static {
        System.loadLibrary("textrender");
    }

    public static native void init();

    public static native void trick();

    public static native void free();

    public static native void resize(int width , int height);
}
