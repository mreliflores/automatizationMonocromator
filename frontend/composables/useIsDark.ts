export const useIsDark = () => {
    const isDark = useState<Boolean>(
        'darkTheme',
        () => true
    )

    const setIsDark = () => {
        isDark.value = !isDark.value
    }

    return {
        isDark,
        setIsDark
    }
}