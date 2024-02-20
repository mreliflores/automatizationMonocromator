export const useIsDark = () => {
    const isDark = useState<Boolean>(
        'darkTheme',
        () => false
    )

    const setIsDark = () => {
        isDark.value = !isDark.value
    }

    return {
        isDark,
        setIsDark
    }
}